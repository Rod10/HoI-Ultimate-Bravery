namespace HoI_Ultimate_Bravery.Classes
{
    public class Idea
    {
        public Dictionary<string, object>? Allowed = new Dictionary<string, object>();
        public Dictionary<string, object>? AllowedCivilWar = new Dictionary<string, object>();
        public int? RemovalCost;
        public Dictionary<string, object>? Modifier = new Dictionary<string, object>();
        public Dictionary<string, object>? Rule = new Dictionary<string, object>();
        public Dictionary<string, object>? ResearchBonus = new Dictionary<string, object>();
        public Dictionary<string, object>? EquipmentBonus = new Dictionary<string, object>();
        public Dictionary<string, object>? Cancel = new Dictionary<string, object>();
        public Dictionary<string, object>? OnAdd = new Dictionary<string, object>();
        public Dictionary<string, object>? OnRemove = new Dictionary<string, object>();
        public Dictionary<string, object>? DoEffect = new Dictionary<string, object>();
        public Dictionary<string, object>? TargetedModifier = new Dictionary<string, object>();
        public string? Picture;
        public string? Name;
    }
}