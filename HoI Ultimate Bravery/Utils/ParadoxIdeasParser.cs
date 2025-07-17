// ParadoxIdeasParser.cs (Patched for correct idea nesting)
using HoI_Ultimate_Bravery.Classes;
using HoI_Ultimate_Bravery.Classes.Ideas;
using System;
using System.Collections.Generic;
using System.IO;
using System.Text.RegularExpressions;

namespace HoI_Ultimate_Bravery.Utils
{
    internal class ParadoxIdeasParser
    {
        internal static Ideas ParseIdeas(TextReader reader)
        {
            var result = new Ideas();
            result.ideas = new Dictionary<string, List<Idea>>();

            string? line;
            bool insideIdeasRoot = false;
            string? currentGroup = null;
            string? currentIdeaName = null;

            Stack<object> contextStack = new();
            Dictionary<string, dynamic>? currentBlock = null;
            Dictionary<string, dynamic>? currentIdeaSubBlock = null;
            Idea? currentIdea = null;

            while ((line = reader.ReadLine()) != null)
            {
                line = line.Trim();
                line = line.Replace(" ", "");

                if (string.IsNullOrEmpty(line) || line.StartsWith("#"))
                    continue;

                // Opening of root "ideas = {"
                if (!insideIdeasRoot && line.StartsWith("ideas") && line.EndsWith("{"))
                {
                    insideIdeasRoot = true;
                    continue;
                }

                // Exit from "ideas" block
                if (insideIdeasRoot && line == "}")
                {
                    if (contextStack.Count > 0)
                    {
                        var popped = contextStack.Pop();
                        if (popped is string groupKey)
                        {
                            currentGroup = null;
                        }
                    }
                    else
                    {
                        insideIdeasRoot = false;
                    }

                    continue;
                }

                if (insideIdeasRoot && line.EndsWith("{"))
                {
                    string key = line[..^1].Trim().TrimEnd('=').Trim();

                    // Inside ideas root, opening new group block
                    if (currentGroup == null)
                    {
                        currentGroup = key;

                        if (!result.ideas.ContainsKey(currentGroup))
                            result.ideas[currentGroup] = new List<Idea>();

                        contextStack.Push(currentGroup);
                    }
                    // Inside a group, opening new idea block
                    else if (currentIdea == null)
                    {
                        currentIdeaName = key;
                        currentIdea = new Idea();
                        currentIdeaSubBlock = new Dictionary<string, dynamic>();
                        currentIdea.idea[currentIdeaName] = currentIdeaSubBlock;
                        result.ideas[currentGroup].Add(currentIdea);
                        contextStack.Push(currentIdea);
                        contextStack.Push(currentIdeaSubBlock);
                        currentBlock = currentIdeaSubBlock;
                    }
                    // Inside an idea, opening nested block
                    else
                    {
                        var nested = new Dictionary<string, dynamic>();
                        currentBlock![key] = nested;
                        contextStack.Push(currentBlock);
                        currentBlock = nested;
                    }

                    continue;
                }

                if (line == "}")
                {
                    if (contextStack.Count > 0)
                    {
                        var popped = contextStack.Pop();

                        if (popped is Dictionary<string, dynamic> block)
                        {
                            currentBlock = block;
                        }
                        else if (popped is Idea)
                        {
                            currentIdea = null;
                            currentIdeaName = null;
                            currentBlock = currentIdeaSubBlock;
                        }
                        else if (popped is string)
                        {
                            currentGroup = null;
                        }
                    }

                    continue;
                }

                if (currentBlock != null && line.Contains('='))
                {
                    var parts = line.Split('=', 2);
                    var key = parts[0].Trim();
                    var value = parts[1].Trim();

                    if (value == "{")
                    {
                        var nested = new Dictionary<string, dynamic>();
                        currentBlock[key] = nested;
                        contextStack.Push(currentBlock);
                        currentBlock = nested;
                    }
                    else
                    {
                        currentBlock[key] = value;
                    }
                }
            }

            return result;
        }

        private static List<ModEffect> ParseEffectList(TextReader reader)
        {
            var list = new List<ModEffect>();
            string? line;

            while ((line = reader.ReadLine()) != null)
            {
                line = line.Trim();
                if (line == "}")
                    break;

                if (line.Contains("="))
                {
                    var match = Regex.Match(line, "(\\w+)\\s*=\\s*(.+)");
                    if (match.Success)
                    {
                        list.Add(new ModEffect
                        {
                            key = match.Groups[1].Value,
                            value = match.Groups[2].Value
                        });
                    }
                }
            }

            return list;
        }
    }
}
