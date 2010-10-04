using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Xml;
using System.Xml.Xsl;
using System.IO;

namespace ZapSpyGui
{
    public partial class ShowXmlForm : Form
    {
        public ShowXmlForm()
        {
            InitializeComponent();
        }
        private static Stream StringToStream(string aString)
        {
            return new System.IO.MemoryStream(new UTF8Encoding().GetBytes(aString));
        }
        private static string FixLineBreaks(string aString)
        {
            if (!aString.Contains("\r"))
            {
                return aString.Replace("\n", "\r\n");
            }
            return aString;
        }
        public string XmlContent
        {
            set
            {
                var styleSheetXmlReader = XmlReader.Create(StringToStream(Resource1.defaultss));
                var xct = new XslCompiledTransform();
                xct.Load(styleSheetXmlReader);

                var stringBuilder = new StringBuilder();
                var xmlWriter = XmlWriter.Create(stringBuilder);

                var documentXmlReader = XmlReader.Create(StringToStream(value));

                xct.Transform(documentXmlReader, xmlWriter);

                string results = stringBuilder.ToString();
                iWebBrowser.DocumentText = results;
                //var stream = StringToStream(stringBuilder.ToString());
                //iWebBrowser.DocumentStream = stream;
                iTextBox.Text = FixLineBreaks(value);
            }
        }
    }
}
