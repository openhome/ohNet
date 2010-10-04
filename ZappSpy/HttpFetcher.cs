using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ZappSpy
{
    public interface IHttpFetcher
    {
        string SynchronousGetRequest(Uri aTargetUri);
    }

    public class HttpFetcher : IHttpFetcher
    {
        public string SynchronousGetRequest(Uri aTargetUri)
        {
            var request = System.Net.HttpWebRequest.Create(aTargetUri);
            var response = request.GetResponse();
            using (var textReader = new System.IO.StreamReader(response.GetResponseStream()))
            {
                return textReader.ReadToEnd();
            }
        }
    }
}

