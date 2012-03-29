
/**
* The ohnet object is the single global object used by ohnet Services to
* facilitate actions and subscriptions. 
* @module ohnet
* @title ohnet
*/

if (typeof ohnet == "undefined" || !ohnet) {
    /**
    * The ohnet global namespace object.  If ohnet is already defined, the
    * existing ohnet object will not be overwritten so that defined
    * namespaces are preserved.
    * @class ohnet
    * @static
    */
    var ohnet = {};
}

/**
* A wrapper for sending and receiving soap messages via jQuery ajax
* @namespace ohnet
* @class soaprequest
*/

ohnet.soaprequest = function (action, url, domain, type, version) {
    this.action = action; // The action to invoke
    this.url = url; // The soap web service url
    this.type = type;
    this.version = version;
    this.domain = domain;
    this.envelope = ""; // The soap envelope
    this.writeEnvelopeStart(action);
}

/**
* Builds the start of the soap message
* @method writeEnvelopeStart
*/
ohnet.soaprequest.prototype.writeEnvelopeStart = function () {
    var envelopeStart = '<?xml version="1.0"?>' +
        '<s:Envelope xmlns:s="http://schemas.xmlsoap.org/soap/envelope/">' +
        '<s:Body s:encodingStyle="http://schemas.xmlsoap.org/soap/encoding/"><u:';

    this.envelope += envelopeStart;
    this.envelope += this.action;
    this.envelope += ' xmlns:u="urn:';
    this.envelope += this.domain;
    this.envelope += ':service:';
    this.envelope += this.type;
    this.envelope += ':';
    this.envelope += this.version;
    this.envelope += '">';
}


/**
* Builds the end of the soap message
* @method writeEnvelopeEnd
*/
ohnet.soaprequest.prototype.writeEnvelopeEnd = function () {
    this.envelope += "</u:";
    this.envelope += this.action;
    this.envelope += "></s:Body></s:Envelope>";
}


/**
* Builds the action of the soap message
* @method getSoapAction
*/
ohnet.soaprequest.prototype.getSoapAction = function () {
    var soapAction = 'urn:';
    soapAction += this.domain;
    soapAction += ':service:';
    soapAction += this.type;
    soapAction += ':';
    soapAction += this.version;
    soapAction += '#';
    soapAction += this.action;
    return soapAction;
}


/**
* Executes the ajax request
* @method send
* @param {Function} successFunction The function to execute once the ajax request returns
* @param {Function} errorFunction The function to execute if an error occurs in the ajax request
*/
ohnet.soaprequest.prototype.send = function (successFunction, errorFunction) {
    var _this = this;
    this.writeEnvelopeEnd();
    return this.createAjaxRequest(
		function (transport) {
		    if (transport.responseXML.getElementsByTagName("faultcode").length > 0) {
		        errorFunction(_this.getTransportErrorMessage(transport), transport);
		    } else {

		        var outParameters = transport.responseXML.getElementsByTagNameNS("*", _this.action + "Response")[0].childNodes;

		        // Parse the output
		        var result = {};
		        for (var i = 0, il = outParameters.length; i < il; i++) {
		            var nodeValue = "";
		            // one result is expected
		            var children = outParameters[i].childNodes;
		            if (children.length > 0) {
		                nodeValue = children[0].nodeValue;
		            }
		            result[outParameters[i].nodeName] = (nodeValue != "" ? nodeValue : null);
		        }
		        successFunction(result);

		    }
		},
		function (transport) {
		    if (errorFunction) {
		        errorFunction(_this.getTransportErrorMessage(transport), transport);
		    }
		    else {
		        defaultErrorFunction(XMLHttpRequest, errorType, errorThrown);
		    }
		}
	);
}



/**
* A wrapper of the ajax request
* @method createAjaxRequest
* @param {Function} successFunction The function to execute once the ajax request returns
* @param {Function} errorFunction The function to execute if an error occurs in the ajax request
*/
ohnet.soaprequest.prototype.createAjaxRequest = function (successFunction, errorFunction) {

    var request = window.XMLHttpRequest ? new XMLHttpRequest() : new ActiveXObject('Microsoft.XMLHTTP');

    request.onreadystatechange = function () {
        if (request.readyState != 4)
            return;
        if (request.status == 200) {
            if (successFunction)
                successFunction(request);
        }
        else {
            if (errorFunction)
                errorFunction(request);
        }
    };

    request.open('POST', this.url, true);
    request.setRequestHeader('SOAPAction', this.getSoapAction());
    request.setRequestHeader('Content-type', 'application/x-www-form-urlencoded');
    request.send(this.envelope);
}

/**
* Provides a default error handler to output the error to console
* @method defaultErrorFunction
* @param {Object} XMLHttpRequest The XMLHTTPRequest
* @param {String} textStatus The error type
* @param {Object} errorThrown The exception object if applicable
*/
ohnet.soaprequest.prototype.defaultErrorFunction = function (XMLHttpRequest, textStatus, errorThrown) {
    console.log("defaultErrorFunction/XMLHttpRequest: " + XMLHttpRequest);
    console.log("defaultErrorFunction/textStatus: " + textStatus);
    console.log("defaultErrorFunction/errorThrown: " + errorThrown);
}


/**
* Parses the SOAP error message into a readable string
* @method getTransportErrorMessage
* @param {Object} transport The XMLHttpRequest object
* @return {String} A readable error message
*/
ohnet.soaprequest.prototype.getTransportErrorMessage = function (transport) {
    var errorString = "Error:";
    try {
        errorString += "\nstatus: " + transport.statusText;
    } catch (e) { }
    if (transport && transport.responseXML) {
        if (transport.responseXML.getElementsByTagName("faultcode").length) {
            errorString += "\nfaultcode: " + transport.responseXML.getElementsByTagName("faultcode")[0].childNodes[0].nodeValue;
        }
        if (transport.responseXML.getElementsByTagName("faultstring").length) {
            errorString += "\nfaultstring: " + transport.responseXML.getElementsByTagName("faultstring")[0].childNodes[0].nodeValue;
        }
        if (transport.responseXML.getElementsByTagName("errorCode").length) {
            errorString += "\nerrorCode: " + transport.responseXML.getElementsByTagName("errorCode")[0].childNodes[0].nodeValue;
        }
        if (transport.responseXML.getElementsByTagName("errorDescription").length) {
            errorString += "\nerrorDescription: " + transport.responseXML.getElementsByTagName("errorDescription")[0].childNodes[0].nodeValue;
        }
    }
    return errorString;
}


/**
* Helper to Read an Int
* @method readIntParameter
* @param {String} value The value to be read as an Integer
* @static
* @return {Int} The integer value
*/
ohnet.soaprequest.readIntParameter = function (value) {
    return value * 1;
}

/**
* Helper to Read an Bool
* @method readBoolParameter
* @param {String} value The value to be read as a Boolean
* @static
* @return {Boolean} The boolean value
*/
ohnet.soaprequest.readBoolParameter = function (value) {
    return (value == "1" || value == "true" || value == "yes") ? true : false;
}

/**
* Helper to Read a String
* @method readStringParameter
* @param {String} value The value to be read as a String (no logic required)
* @static
* @return {String} The string value
*/
ohnet.soaprequest.readStringParameter = function (value) {
    return value;
}

/**
* Helper to Read a Binary
* @method readBinaryParameter
* @param {String} value The value to be read as a String (no logic required)
* @static
* @return {String} The binary value converted from base64
*/
ohnet.soaprequest.readBinaryParameter = function (value) {
	return atob	? atob(value) : ohnet.base64_decode(value);
}

/**
* Helper to write an Integer into a xml tag
* @method writeIntParameter
* @param {String} tagName The xml tag name to be inserted into the SOAP envelope
* @param {String} value The xml tag value to be inserted into the SOAP envelope
*/
ohnet.soaprequest.prototype.writeIntParameter = function (tagName, value) {
    this.writeParameter(tagName, "" + (value ? value : "0"));
}

/**
* Helper to write a Boolean into a xml tag
* @method writeBoolParameter
* @param {String} tagName The xml tag name to be inserted into the SOAP envelope
* @param {String} value The xml tag value to be inserted into the SOAP envelope
*/
ohnet.soaprequest.prototype.writeBoolParameter = function (tagName, value) {
    this.writeParameter(tagName, value ? "1" : "0");
}

/**
* Helper to write a String into a xml tag
* @method writeBoolParameter
* @param {String} tagName The xml tag name to be inserted into the SOAP envelope
* @param {String} value The xml tag value to be inserted into the SOAP envelope
*/
ohnet.soaprequest.prototype.writeStringParameter = function (tagName, value) {
    this.writeParameter(tagName, (value ? value : ""));
}

/**
* Helper to write Binary into a xml tag
* @method writeBinaryParameter
* @param {String} tagName The xml tag name to be inserted into the SOAP envelope
* @param {String} value The xml tag value to be inserted into the SOAP envelope
*/
ohnet.soaprequest.prototype.writeBinaryParameter = function (tagName, value) {
    this.writeParameter(tagName, (value ? (btoa ? btoa(value) : ohnet.base64_encode(value)) : ""));
}


/**
* Helper to format the tag and value into a xml tag and insert into the SOAP enveloper
* @method writeParameter
* @param {String} tagName The xml tag name to be inserted into the SOAP envelope
* @param {String} value The xml tag value to be inserted into the SOAP envelope
*/
ohnet.soaprequest.prototype.writeParameter = function (tagName, value) {
    this.envelope += "<" + tagName + ">" + value.replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;") + "</" + tagName + ">";
}