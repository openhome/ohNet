using System;
using System.Collections.Generic;
using System.IO;
using System.Diagnostics;

namespace Zapp
{
    class TemplateFile
    {
        private String iTemplate;
        private String iOutputExt;
        private String iOutputNameAdornment;
        private String iCustomArgs;
        
        public String Template
        {
            get { return iTemplate; }
        }
        public String Ext
        {
            get { return iOutputExt; }
        }
        public string OutputNameAdornment
        {
            get { return iOutputNameAdornment; }
        }
        public String Args
        {
            get { return iCustomArgs; }
        }
        public TemplateFile(String aTemplateName, String aOutputExt)
        {
            Construct(aTemplateName, aOutputExt, "", "");
        }
        public TemplateFile(String aTemplateName, String aOutputExt, String aOutputNameAdornment)
        {
            Construct(aTemplateName, aOutputExt, aOutputNameAdornment, "");
        }
        public TemplateFile(String aTemplateName, String aOutputExt, String aOutputNameAdornment, String aCustomArgs)
        {
            Construct(aTemplateName, aOutputExt, aOutputNameAdornment, aCustomArgs);
        }
        private void Construct(String aTemplateName, String aOutputExt, String aOutputNameAdornment, String aCustomArgs)
        {
            iTemplate = aTemplateName;
            iOutputExt = aOutputExt;
            iOutputNameAdornment = aOutputNameAdornment;
            iCustomArgs = aCustomArgs;
        }
    }
    
    class Program
    {
        enum ETargetLanguage
        {
            eUndefined,
            eCpp,
            eCppCore,
            eC,
            eCs,
            eJs
        }
        enum ETargetStack
        {
            eUndefined,
            eCp,
            eDv
        }
        
        public static void Main(string[] args)
        {
            ETargetLanguage language = ETargetLanguage.eUndefined;
            ETargetStack stack       = ETargetStack.eUndefined;
            String xmlInput          = "";
            String outputDir         = "";
            String domain            = "";
            String type              = "";
            uint version             = 0;

            foreach (string arg in args)
            {
                string[] var = arg.Split(new char[]{'='}, 2);
                if (var[0] == "--language")
                {
                    if (var[1] == "cpp")
                    {
                        language = ETargetLanguage.eCpp;
                    }
                    else if (var[1] == "cppcore")
                    {
                        language = ETargetLanguage.eCppCore;
                    }
                    else if (var[1] == "c")
                    {
                        language = ETargetLanguage.eC;
                    }
                    else if (var[1] == "cs")
                    {
                        language = ETargetLanguage.eCs;
                    }
                    else if (var[1] == "js")
                    {
                        language = ETargetLanguage.eJs;
                    }
                    else
                    {
                        Console.WriteLine("ERROR: Unsupported language - " + var[1]);
                        Program.PrintUsage();
                        return;
                    }
                }
                else if (var[0] == "--stack")
                {
                    if (var[1] == "cp")
                    {
                        stack = ETargetStack.eCp;
                    }
                    else if (var[1] == "dv")
                    {
                        stack = ETargetStack.eDv;
                    }
                    else
                    {
                        Console.WriteLine("ERROR: Unsupported stack - " + var[1]);
                        Program.PrintUsage();
                        return;
                    }
                }
                else if (var[0] == "--xml")
                {
                    xmlInput = var[1];
                }
                else if (var[0] == "--output")
                {
                    outputDir = var[1];
                }
                else if (var[0] == "--domain")
                {
                    domain = var[1];
                }
                else if (var[0] == "--type")
                {
                    type = var[1];
                }
                else if (var[0] == "--version")
                {
                    version = Convert.ToUInt32(var[1]);
                }
                else
                {
                    Console.WriteLine("ERROR: Unrecognised switch - " + arg);
                    Program.PrintUsage();
                    return;
                }
            }

            if (language == ETargetLanguage.eUndefined || stack == ETargetStack.eUndefined || xmlInput.Length == 0 ||
                outputDir.Length == 0 || domain.Length == 0 || type.Length == 0 || version == 0)
            {
                Program.PrintUsage();
                return;
            }

            List<TemplateFile> templates = new List<TemplateFile>();
            switch (language)
            {
                case ETargetLanguage.eCpp:
                    if (stack == ETargetStack.eCp)
                    {
                        templates.Add(new TemplateFile("CpUpnpCppHeader.tt", ".h", "", "-a buffer:0"));
                        templates.Add(new TemplateFile("CpUpnpCppStringSource.tt", ".cpp", "Std"));
                    }
                    else
                    {
                        templates.Add(new TemplateFile("DvUpnpCppStdHeader.tt", ".h"));
                        templates.Add(new TemplateFile("DvUpnpCppStdSource.tt", ".cpp", "Std"));
                    }
                    break;
                case ETargetLanguage.eCppCore:
                    if (stack == ETargetStack.eCp)
                    {
                        templates.Add(new TemplateFile("CpUpnpCppHeader.tt", ".h", "", "-a buffer:1"));
                        templates.Add(new TemplateFile("CpUpnpCppBufferSource.tt", ".cpp"));
                    }
                    else
                    {
                        templates.Add(new TemplateFile("DvUpnpCppCoreHeader.tt", ".h"));
                        templates.Add(new TemplateFile("DvUpnpCppCoreSource.tt", ".cpp"));
                    }
                    break;
                case ETargetLanguage.eC:
                    if (stack == ETargetStack.eCp)
                    {
                        templates.Add(new TemplateFile("CpUpnpCHeader.tt", ".h"));
                        templates.Add(new TemplateFile("CpUpnpCSource.tt", ".cpp", "C"));
                        //templates.Add(new TemplateFile("CpUpnpCppHeader.tt", ".h", "", "-a buffer:1"));
                        //templates.Add(new TemplateFile("CpUpnpCppBufferSource.tt", ".cpp"));
                    }
                    else
                    {
                        templates.Add(new TemplateFile("DvUpnpCHeader.tt", ".h", "C"));
                        templates.Add(new TemplateFile("DvUpnpCSource.tt", ".cpp", "C"));
                        templates.Add(new TemplateFile("DvUpnpCppCoreHeader.tt", ".h"));
                        templates.Add(new TemplateFile("DvUpnpCppCoreSource.tt", ".cpp"));
                    }
                    break;
                case ETargetLanguage.eCs:
                    if (stack == ETargetStack.eCp)
                    {
                        templates.Add(new TemplateFile("CpUpnpCs.tt", ".cs"));
                    }
                    else
                    {
                        templates.Add(new TemplateFile("DvUpnpCs.tt", ".cs"));
                    }
                    break;
                case ETargetLanguage.eJs:
                    if (stack != ETargetStack.eCp)
                    {
                        Console.WriteLine("ERROR: Js only supported for the --stack=cp");
                        return;
                    }
                    templates.Add(new TemplateFile("CpUpnpJs.tt", ".js"));
                    break;
            }

            String upnpdomain = domain.Replace(".", "-");
            if (upnpdomain.StartsWith("upnp-"))
            {
                upnpdomain = "schemas-" + upnpdomain;
            }
            String outputFileName = "";
            char[] charSeparators = new char[] { '.' };
            String[] res = domain.Split(charSeparators, StringSplitOptions.None);
            foreach (String str in res)
            {
                outputFileName += str.Substring(0, 1).ToUpper();
                if (str.Length > 1)
                {
                    outputFileName += str.Substring(1, str.Length - 1);
                }
            }
            outputFileName += type + version;
            if (stack == ETargetStack.eCp)
            {
                outputFileName = "Cp" + outputFileName;
            }
            else
            {
                outputFileName = "Dv" + outputFileName;
            }

            String ttPath = Path.Combine(Directory.GetCurrentDirectory(), Environment.GetCommandLineArgs()[0]);
            ttPath = Path.GetDirectoryName(ttPath);
            for (int i = 0; i < templates.Count; i++)
            {
                ProcessStartInfo startInfo = new ProcessStartInfo();
                startInfo.FileName = Path.Combine(ttPath, "TextTransform.exe");
                String ttArgs = String.Format("-o {0}{1}{2}{3} T4/Templates/{4} -a \"xml:{5}\" -a domain:{6} -a type:{7} -a version:{8} {9}",
                                                outputDir, outputFileName, templates[i].OutputNameAdornment, templates[i].Ext, templates[i].Template, xmlInput, domain, type, version, templates[i].Args);
                startInfo.Arguments = ttArgs;
                startInfo.RedirectStandardOutput = true;
                startInfo.UseShellExecute = false;
                startInfo.CreateNoWindow = true;
                Process proc = Process.Start(startInfo);
                proc.WaitForExit();
            }
        }

        private static void PrintUsage()
        {
            Console.WriteLine("Usage is ZappGen");
            Console.WriteLine("\t--language=[cpp|cppcore|c|cs|js]");
            Console.WriteLine("\t--stack=[cp|dv]");
            Console.WriteLine("\t--xml=[path + name of xml service description]");
            Console.WriteLine("\t--output=[dir for generated files]");
            Console.WriteLine("\t--domain=[service domain]");
            Console.WriteLine("\t--type=[service type]");
            Console.WriteLine("\t--version=[service version]");
        }
    }
}
