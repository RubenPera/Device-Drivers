using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace ReadOutput
{
    class Export
    {
        public Header Header { get; set; }
        public IEnumerable<Line> Lines { get; set; }

        public Export(Header header, IEnumerable<Line> lines)
        {
            Header = header;
            Lines = lines;
        }
    }

    class Header
    {
        public int StartState { get; set; }
        public int States { get; set; }
        public string Name { get; set; }

        public Header(string[] split_line, string name)
        {
            StartState = int.Parse(split_line[0]);
            States = int.Parse(split_line[2]);
            Name = name;
        }
    }

    class Line
    {
        public int State { get; set; }
        public int NextState { get; set; }
        public int Action { get; set; }
        public string ActionString { get; set; }

        public Line(string[] split_line)
        {
            State = int.Parse(split_line[0]);
            ActionString = split_line[1];
            NextState = int.Parse(split_line[2]);
            Action = -1;
        }

        public Line UpdateAction(Dictionary<string, int> actions)
        {
            if (actions.ContainsKey(ActionString))
            {
                Action = actions[ActionString];
            }
            else
            {
                Action = actions.Count;
                actions[ActionString] = Action;
            }

            return this;
        }

        public string Display => $"[{State}, {Action}, {NextState}]";
    }

    class Program
    {
        static void Main(string[] args)
        {
            var output = new StringBuilder();

            var fileNames = new List<string>
            {
                "CONTROLLER_EXPORT",
                "STDIN_EXPORT",
                "STDOUT_EXPORT"
            };

            var actions = GetActions();
            var exports = fileNames.Select(f => GetExport(f, actions));

            int ACTIONS = actions.Count;
            int STATES = exports.Max(e => e.Header.States);

            PrintActions(actions, output);

            PrintExports(ACTIONS, STATES, exports, output);

            PrintDefines(ACTIONS, STATES, output);

            WriteFileLines(output.ToString());
        }

        static void PrintDefines(int actions, int states, StringBuilder output)
        {
            output.AppendLine($"ACTIONS = {actions}");
            output.AppendLine($"STATES = {states}");
        }

        static Export GetExport(string name, Dictionary<string, int> actions)
        {
            var fileLines = GetFileLines(name).ToList();

            var lines = fileLines.Skip(1).Select(l => new Line(CleanSeperatedLines(l)));

            var linesWithAction = lines.Select(l => l.UpdateAction(actions));

            return new Export(
                new Header(CleanSeperatedLines(fileLines[0]), name),
                linesWithAction
                );
        }

        static void DrawGrid(int width, int height, Export export, StringBuilder output)
        {
            IEnumerable<Line> lines = null;
            string valueToWrite = null;
            int w = 0, h = 0;

            output.AppendLine();
            output.AppendLine(export.Header.Name);

            export.Lines.ToList().ForEach(l => Console.WriteLine(l.Display));

            output.AppendLine("{");
            for (h = 0; h < height; h++)
            {
                output.Append("{");
                for (w = 0; w < width; w++)
                {
                    lines = export.Lines.Where(l => l.State == h && l.Action == w);
                    valueToWrite = "-1";

                    if (lines.Any())
                    {
                        valueToWrite = lines.First().NextState.ToString();
                    }
                    output.Append($"{valueToWrite},");
                }
                output.AppendLine("},");
            }
            output.AppendLine("}");
        }

        static Dictionary<string, int> GetActions()
        {
            var combinedLines = GetFileLines("COMBINED").Where(l => !l.Contains("des"));
            var actions = new Dictionary<string, int>();

            var lineWithoutAction = combinedLines.Select(l => new Line(CleanSeperatedLines(l)));
            FillActions(lineWithoutAction, actions);

            return actions;
        }

        public static void PrintActions(Dictionary<string, int> actions, StringBuilder output)
        {
            foreach (var action in actions)
            {
                output.AppendLine($"{action.Key} {action.Value}");
            }
        }

        public static void PrintExports(int width, int height, IEnumerable<Export> exports, StringBuilder output) => exports.ToList().ForEach(e => DrawGrid(width, height, e, output));

        public static IEnumerable<string> GetFileLines(string name) => File.ReadLines(FileLocation(name, "aut"));

        public static void WriteFileLines(string output) => File.WriteAllText(FileLocation("output", "txt"), output);

        static string FileLocation(string name, string extension) => $"{Directory.GetCurrentDirectory()}\\out\\{name}.{extension}";

        static void PrintAllLines(IEnumerable<string> lines) => lines.ToList().ForEach(l => Console.WriteLine(l));

        static void FillActions(IEnumerable<Line> lines, Dictionary<string, int> actions) => lines.ToList().ForEach(l => l.UpdateAction(actions));

        static string[] CleanSeperatedLines(string line) => line.Replace("des", "").Replace("(", "").Replace(")", "").Split(",");
    }
}
