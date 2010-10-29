var kEnvelopeStart = '<?xml version="1.0"?>' +
        '<s:Envelope xmlns:s="http://schemas.xmlsoap.org/soap/envelope/">' +
        '<s:Body s:encodingStyle="http://schemas.xmlsoap.org/soap/encoding/"><u:';
		
var kAjaxTimeout = 10000;

var SoapRequest = function(aAction, aUrl, aDomain, aType, aVersion){
	this.iAction = aAction;
	this.iUrl = aUrl;
	this.iType = aType;
	this.iVersion = aVersion;
	this.iDomain = aDomain;
	this.iEnvelope = "";	
	this.WriteEnvelopeStart(aAction);
}

SoapRequest.prototype.WriteEnvelopeStart = function() {
	this.iEnvelope += kEnvelopeStart;
	this.iEnvelope += this.iAction;
	this.iEnvelope += ' xmlns:u="urn:';
	this.iEnvelope += this.iDomain;
	this.iEnvelope += ':service:';
	this.iEnvelope += this.iType;
	this.iEnvelope += ':';
	this.iEnvelope += this.iVersion;
	this.iEnvelope += '">';
}

SoapRequest.prototype.WriteEnvelopeEnd = function(){
	this.iEnvelope += "</u:";
	this.iEnvelope += this.iAction;
	this.iEnvelope += "></s:Body></s:Envelope>";
}
	
SoapRequest.prototype.GetSoapAction = function(){
	var soapAction = 'urn:';
	soapAction += this.iDomain;
	soapAction += ':service:';
	soapAction += this.iType;
	soapAction += ':';
	soapAction += this.iVersion;
	soapAction += '#';
	soapAction += this.iAction;
	return soapAction;
}
	
SoapRequest.prototype.CreateAjaxRequest = function(aCallbackFunction, aErrorFunction) {
	var thisObj = this;
	return new Ajax.Request(
	this.iUrl , {
		method: 'post', 
		requestHeaders: ["SOAPAction", this.GetSoapAction()],
		postBody: this.iEnvelope, 
		onSuccess: function(transport) {			
			if (transport.status){
				if (aCallbackFunction) { 
					try { 
						aCallbackFunction(transport); 
					}catch (e) {
						debug.log("Exception caught in callback" + e.message);      
						if (aErrorFunction) { aErrorFunction(transport); };
					}
				}
			}else{                
				debug.log("Request has no transport status: " + thisObj.iUrl);       
				if (aErrorFunction) { aErrorFunction(transport); };
			}
		},
		onFailure : function (transport){     
			debug.log("Request failed: " + thisObj.iUrl);       
			if (aErrorFunction) { aErrorFunction(transport); };
		},
		onException : function (transport){     
			debug.log("Request exception: " + thisObj.iUrl);       
			if (aErrorFunction) { aErrorFunction(transport); };
		},
		contentType: "text/xml"
	}); 
};
	
SoapRequest.prototype.getElementsByTagNameNS = function(tagName, ns, scope){
	var elementListForReturn = scope.getElementsByTagName(ns+":"+tagName);
	if(elementListForReturn.length == 0){
		elementListForReturn = scope.getElementsByTagName(tagName);
		if(elementListForReturn.length == 0 && document.getElementsByTagNameNS){
			elementListForReturn = scope.getElementsByTagNameNS(ns, tagName);
		}
	}     
	return elementListForReturn;
}

SoapRequest.prototype.ReadIntParameter = function(aValue) {
	return aValue * 1;
}

SoapRequest.prototype.ReadBoolParameter = function(aValue) {
	return (aValue == "1") ? true : false;
}

SoapRequest.prototype.ReadStringParameter = function(aValue) {
	return aValue;
}

SoapRequest.prototype.ReadBinaryParameter = function(aValue) {
	return aValue;
}

SoapRequest.prototype.WriteIntParameter = function(aTagName, aValue) {
	this.WriteParameter(aTagName, "" + (aValue?aValue:"0"));
}

SoapRequest.prototype.WriteBoolParameter = function(aTagName, aValue) {
	this.WriteParameter(aTagName, aValue ? "1" : "0");
}

SoapRequest.prototype.WriteStringParameter = function(aTagName, aValue) {
	this.WriteParameter(aTagName, (aValue?aValue:""));
}

SoapRequest.prototype.WriteBinaryParameter = function(aTagName, aValue) {
	this.WriteParameter(aTagName, (aValue?aValue:""));
}

SoapRequest.prototype.WriteParameter = function(aTagName, aValue) {
	this.iEnvelope += "<" + aTagName + ">" + aValue.replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;") + "</" + aTagName + ">";
}

SoapRequest.prototype.GetTransportErrorMessage = function(transport) {
	var errorString = "Error:";
	try{
		errorString += "\nstatus: " + transport.statusText;
	}catch(e){}
	if (transport && transport.responseXML){
		if (transport.responseXML.getElementsByTagName("faultcode").length){				
			errorString += "\nfaultcode: " + transport.responseXML.getElementsByTagName("faultcode")[0].childNodes[0].nodeValue;
		}
		if (transport.responseXML.getElementsByTagName("faultstring").length){				
			errorString += "\nfaultstring: " + transport.responseXML.getElementsByTagName("faultstring")[0].childNodes[0].nodeValue;
		}
		if (transport.responseXML.getElementsByTagName("errorCode").length){				
			errorString += "\nerrorCode: " + transport.responseXML.getElementsByTagName("errorCode")[0].childNodes[0].nodeValue;
		}
		if (transport.responseXML.getElementsByTagName("errorDescription").length){				
			errorString += "\nerrorDescription: " + transport.responseXML.getElementsByTagName("errorDescription")[0].childNodes[0].nodeValue;
		}
	}
	return errorString;
}

SoapRequest.prototype.Send = function(onSuccess, onError) {
	var thisObj = this;
	this.WriteEnvelopeEnd();
	return this.CreateAjaxRequest(
		function(transport){
			if(transport.responseXML.getElementsByTagName("faultcode").length > 0){
				onError(thisObj.GetTransportErrorMessage(transport), transport);
			}else{
				var outParameters = thisObj.getElementsByTagNameNS(thisObj.iAction + "Response", "u", transport.responseXML)[0].childNodes;
				var result = {};
				for(var i=0;i<outParameters.length;i++){
					var nodeValue = "";
					var childNodes = outParameters[i].childNodes;
					for (var j=0;j<childNodes.length;j++){
						nodeValue += childNodes[j].nodeValue;
					}
					result[outParameters[i].nodeName.replace(/.*:/, "")] = (nodeValue!=""?nodeValue:null);
				}
				onSuccess(result);
			}				
		},
		function(transport){
			onError(thisObj.GetTransportErrorMessage(transport), transport);
		}
	);
}

/* helpers for Ajax comms */

Ajax.Request.prototype.abort = function() {
    // prevent and state change callbacks from being issued
    this.transport.onreadystatechange = Prototype.emptyFunction;
    // abort the XHR
    this.transport.abort();
    // update the request counter
    Ajax.activeRequestCount--;
};

// Register global responders that will occur on all AJAX requests

 Ajax.Responders.register({
        onCreate: function(request) {
            request['timeoutId'] = window.setTimeout(
                function() {
                    if (request.options['onSuccess']){
                        // cancel success function
                        request.options['onSuccess'] = function(){};
                    }
                    debug.log("Request to " + request.url + " has timed out.");
                    request.transport.abort();
                    // Run the onFailure method if we set one up when creating the AJAX object
                    if (request.options['onFailure']) {
                        request.options['onFailure'](request.transport);
                    }
                },
                window["AjaxTimeout"]?window["AjaxTimeout"]:kAjaxTimeout
            );
        },
        onComplete: function(request) {
            // Clear the timeout, the request completed ok
            window.clearTimeout(request['timeoutId']);
        }
});
