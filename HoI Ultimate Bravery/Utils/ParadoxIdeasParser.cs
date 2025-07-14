// ParadoxIdeasParser.cs
using System;
using System.Collections.Generic;
using System.IO;
using System.Text.RegularExpressions;
using HoI_Ultimate_Bravery.Classes.Ideas;

namespace HoI_Ultimate_Bravery.Utils
{
    public class ParadoxIdeasParser
    {
        public static Ideas ParseIdeas(TextReader reader)
        {
            Ideas ideas = new Ideas();
            IdeasDictionnary ideasDictionnary = new IdeasDictionnary();
            Country country = new Country();
            string? line;
            string currentSection = string.Empty;
            Idea? currentIdea = null;
            string? currentIdeaName = null;
            var result = new Dictionary<string, object>();
            string previousLine = null;

            while ((line = reader.ReadLine()) != null)
            {
                line = line.Trim();
                Console.WriteLine(line);
                if (string.IsNullOrEmpty(line) || line.StartsWith("#"))
                    continue;

                // Detect main section
                if (line.StartsWith("ideas") && line.EndsWith("{"))
                {
                    ideas.ideas.Add("ideas", ideasDictionnary);
                    continue; // top-level block
                }

                if (line.StartsWith("country") && line.EndsWith("{"))
                {
                    ideas.ideas.Values.FirstOrDefault().country.Add("country", country);
                    continue; // sub-level block
                }

                if ((line.EndsWith("={") || line.EndsWith(" = {") || line.EndsWith("= {") || line.EndsWith(" ={")) && currentIdeaName == null)
                {
                    // new idea block
                    currentIdea = new Idea();
                    currentIdeaName = line[..line.IndexOf("=")].Trim();
                    continue;
                }
                if (line == "}" && currentIdea != null)
                {
                    if (currentIdea != null && currentIdeaName != null && previousLine == "}")
                    {
                        ideas.ideas.Values.FirstOrDefault().country.Values.FirstOrDefault().idea.Add(currentIdeaName, currentIdea);
                        currentIdea = null;
                        currentIdeaName = null;
                    }
                    previousLine = line;
                    continue;
                }

                if (line.Contains("="))
                {
                    var match = Regex.Match(line, "(\\w+)(\\s*=\\s*)(.+)");
                    if (match.Success)
                    {
                        var key = match.Groups[1].Value;
                        var value = match.Groups[3].Value.Trim();

                        switch (line)
                        {
                            case "allowed":
                                result[key] = value;
                                currentIdea.Allowed = result;
                                break;
                            case "allowed_civil_war":
                                result[key] = value;
                                currentIdea.AllowedCivilWar = result;
                                break;
                            case "modifier":
                                result[key] = value;
                                currentIdea.Modifier = result;
                                break;
                            case "rule":
                                result[key] = value;
                                currentIdea.Rule = result;
                                break;
                            case "research_bonus":
                                result[key] = value;
                                currentIdea.ResearchBonus = result;
                                break;
                            case "equipment_bonus":
                                result[key] = value;
                                currentIdea.EquipmentBonus = result;
                                break;
                            case "removal_cost":
                                if (int.TryParse(value, out int rc))
                                    currentIdea.RemovalCost = rc;
                                break;
                            case "picture":
                                currentIdea.Picture = value;
                                break;
                            case "name":
                                currentIdea.Name = value;
                                break;
                            default:
                                // Fallback for other known blocks or unknown keys
                                break;
                        }
                    }
                }
            }

            return ideas;
        }
    }
}
