var SubscriptionManager = (function () {

    // Private Variables
    var iRenewalPollingInterval = 0;
    var iServices = {};
    var iPort = 0;
    var started = false;
    var socket = null;
    var DEBUG = false;
    var DEBUGPOLL = false;

    //  Private Methods

    function log(msg) {
        if (DEBUG)
            console.log(msg);
    }

    function GenerateSubscriptionId() {
        log("*** GenerateSubscriptionId ***");
        var uid = Math.random().toString(16).replace(".", "") + (new Date()).valueOf().toString(16);
        log("RET :" + uid);
        log("");
        return uid;
    }

    function SubscribeMessage(aService, aTimeoutSeconds) {
        log("*** SubscribeMessage ***");
        log("VAR : Udn :" + aService.Udn());
        log("VAR : Service Name :" + aService.ServiceName());
        log("VAR : Subscription Id :" + aService.SubscriptionId());
        log("VAR : kDefaultTimeOutMinutes:" + SubscriptionManager.kDefaultTimeOutMinutes);
        log("VAR : aTimeoutSeconds:" + aTimeoutSeconds);
        log("CALC : Timeout:" + (aTimeoutSeconds ? aTimeoutSeconds : SubscriptionManager.kDefaultTimeOutMinutes));

        var message = "<?xml verison='1.0' ?>";
        message += "<ROOT>";
        message += "<METHOD>Subscribe</METHOD>";
        message += "<UDN>" + aService.Udn() + "</UDN>";
        message += "<SERVICE>" + aService.ServiceName() + "</SERVICE>";
        message += "<SID>" + aService.SubscriptionId() + "</SID>";
        message += "<NT>upnp:event</NT>";
        message += "<TIMEOUT>" + (aTimeoutSeconds ? aTimeoutSeconds : SubscriptionManager.kDefaultTimeOutMinutes) + "</TIMEOUT>";
        message += "</ROOT>";

        log("RET :" + message);
        log("");
        return message;
    }

    function UnsubscribeMessage(aSubscriptionId) {
        log("*** UnsubscribeMessage ***");
        log("VAR : aSubscriptionId :" + aSubscriptionId);

        var message = "<?xml verison='1.0' ?>";
        message += "<ROOT>";
        message += "<METHOD>Unsubscribe</METHOD>";
        message += "<SID>" + aSubscriptionId + "</SID>";
        message += "</ROOT>";

        log("RET :" + message);
        log("");
        return message;
    }

    function RenewMessage(aSubscriptionId) {
        log("*** RenewMessage ***");
        log("VAR : aSubscriptionId :" + aSubscriptionId);

        var message = "<?xml verison='1.0' ?>";
        message += "<ROOT>";
        message += "<METHOD>Renew</METHOD>";
        message += "<SID>" + aSubscriptionId + "</SID>";
        message += "<TIMEOUT>" + kDefaultSubscriptionTimeoutSeconds + "</TIMEOUT>";
        message += "</ROOT>";

        log("RET :" + message);
        log("");

        return message;
    }

    function SetSubscriptionTimeout(aSubscriptionId, aTimeoutSeconds) {
        log("*** SetSubscriptionTimeout ***");
        log("VAR : aSubscriptionId :" + aSubscriptionId);
        log("VAR : aTimeoutSeconds :" + aTimeoutSeconds);

        if (iServices[aSubscriptionId]) {

            log("CALL : RenewSubscription :" + aTimeoutSeconds * 1000);

            log("CALL : RenewSubscription with kRenewTrigger :" + aTimeoutSeconds * 1000 * SubscriptionManager.kRenewTrigger);
            var timer = setTimeout(function () {
                RenewSubscription(aSubscriptionId);
            }, (aTimeoutSeconds * 1000 * SubscriptionManager.kRenewTrigger));

            iServices[aSubscriptionId].SubscriptionTimer = timer;

            log("CALC :iServices[aSubscriptionId].SubscriptionTimer :" + iServices[aSubscriptionId].SubscriptionTimer);
        }
        else {
            log("NULL : iServices[aSubscriptionId] :" + iServices[aSubscriptionId]);
        }
        log("");
    }

    function ServiceNames() {
        var result = [];
        for (var srv in iServices) {
            result[result.length] = srv;
        }
        return result;
    }

    function SetPropertyUpdate(aSubscriptionId, aPropertyName, aPropertyValue) {
        log("*** SetPropertyUpdate ***");
        log("VAR : aSubscriptionId :" + aSubscriptionId);
        log("VAR : aPropertyName :" + aPropertyName);
        log("VAR : aPropertyValue :" + aPropertyValue);
        if (iServices[aSubscriptionId]) {
            if (iServices[aSubscriptionId].iVariables[aPropertyName]) {
                iServices[aSubscriptionId].iVariables[aPropertyName].SetValue(aPropertyValue);
                log("CALC :iServices[aSubscriptionId].iVariables[aPropertyName].iValue :" + iServices[aSubscriptionId].iVariables[aPropertyName].iValue);
            }
            else {
                log("NULL : iServices[aSubscriptionId].iVariables[aPropertyName] :" + iServices[aSubscriptionId].iVariables[aPropertyName]);
            }
        }
        else {
            log("NULL : iServices[aSubscriptionId] :" + iServices[aSubscriptionId]);
        }
        log("");
    }

    function RenewSubscriptions() {
        if (DEBUGPOLL) {
            log("*** RenewSubscriptions ***");
            var d = new Date();
            log("TIME :" + d.getTime());
        }
        for (var srv in iServices) {
            var service = iServices[srv];
            if (service.SubscriptionTimeoutSec && service.LastRenewed) {
                var timeoutMS = service.SubscriptionTimeoutSec * 1000; // to ms
                var renewDate = service.LastRenewed;
                if (DEBUGPOLL) {
                    log("VAR : service.SubscriptionTimeoutSec :" + service.SubscriptionTimeoutSec);
                    log("VAR : service.LastRenewed :" + service.LastRenewed);
                    log("VAR : timeoutMS :" + timeoutMS);
                    log("VAR : kRenewTrigger :" + SubscriptionManager.kRenewTrigger);
                }
                var now = new Date();
                var diff = now.getTime() - renewDate;

                if (DEBUGPOLL) {
                    log("VAR : now.getTime() :" + now.getTime());
                    log("VAR : diff :" + diff);
                    log("VAR : timeoutMS * SubscriptionManager.kRenewTrigger :" + timeoutMS * SubscriptionManager.kRenewTrigger);
                    log("VAR : diff > (timeoutMS * SubscriptionManager.kRenewTrigger) :" + diff > (timeoutMS * SubscriptionManager.kRenewTrigger));
                }
                if (diff > (timeoutMS * SubscriptionManager.kRenewTrigger) && socket && socket.readyState == 1) {
                    if (DEBUGPOLL)
                        log("CON : Renew Detected");
                    service.LastRenewed = now.getTime();
                    if (DEBUGPOLL) {
                        log("CALC : service.LastRenewed :" + service.LastRenewed);
                        log("CALL : RenewMessage");
                    }
                    socket.send(RenewMessage(service.SubscriptionId(), service.SubscriptionTimeoutSec));
                }
            }
            else {
                if (DEBUGPOLL) {
                    log("NULL : service.SubscriptionTimeoutSec :" + service.SubscriptionTimeoutSec);
                    log("NULL : service.LastRenewed :" + service.LastRenewed);
                }
            }
        }
        log("");
    }

    function RenewSubscription(aSubscriptionId) {
        if (DEBUGPOLL) {
            log("*** RenewSubscription ***");
            log("VAR : aSubscriptionId :" + aSubscriptionId);
            var d = new Date();
            log("TIME :" + d.getMinutes() + " " + d.getSeconds());

        }
        if (iServices[aSubscriptionId]) {
            if (DEBUGPOLL) {
                log("iServices[aSubscriptionId] :" + iServices[aSubscriptionId]);
            }

            if (iServices[aSubscriptionId].SubscriptionTimer) {
                socket.send(RenewMessage(iServices[aSubscriptionId].SubscriptionId()));
            }
            else {
                if (DEBUGPOLL) {
                    log("NULL : (iServices[aSubscriptionId].SubscriptionTimer :" + iServices[aSubscriptionId].SubscriptionTimer);
                }
            }
        }
        else {
            if (DEBUGPOLL) {
                log("NULL : iServices[aSubscriptionId] :" + iServices[aSubscriptionId])
            }
        }
        if (DEBUGPOLL) {
            log("");
        }
    }

    function ReceiveMessage(aMessage) {
        log("*** ReceiveMessage ***");
        log("CON : window.DOMParser : " + window.DOMParser);
        if (window.DOMParser) {
            parser = new DOMParser();
            xmlDoc = parser.parseFromString(aMessage, "text/xml");
            var x = xmlDoc.childNodes;

            x = xmlDoc.getElementsByTagNameNS("*", "METHOD");
            var method = x[0].textContent;
            log("VAR : method : " + method);
            x = xmlDoc.getElementsByTagNameNS("*", "SID");

            var subId = x[0].textContent;
            log("VAR : subId : " + subId);

            if (method == "PropertyUpdate") {
                x = xmlDoc.getElementsByTagNameNS("*", "property");
                for (var i = 0; i < x.length; i++) {
                    var y = x[i].childNodes[0];
                    if (y) {
                        var propertyName = y.tagName;
                        var propertyValue = y.textContent;
                        log("VAR : propertyName : " + propertyName);
                        log("VAR : propertyValue : " + propertyValue);
                        log("CALL : SetPropertyUpdate");
                        SetPropertyUpdate(subId, propertyName, propertyValue);
                    }
                }
            }
            else if (method == "SubscriptionTimeout") {
                x = xmlDoc.getElementsByTagNameNS("*", "TIMEOUT");
                if (x) {
                    log("VAR : timeout : " + x[0].textContent);
                    log("CALL : SetSubscriptionTimeout");

                    if (iServices[subId].aSubscribeSuccessFunction) {
                        iServices[subId].aSubscribeSuccessFunction();
                        iServices[subId].aSubscribeSuccessFunction = null;
                    }
                    SetSubscriptionTimeout(subId, x[0].textContent);
                }
            }
        }
        else // Internet Explorer - TODO REMOVE!
        {
            xmlDoc = new ActiveXObject("Microsoft.XMLDOM");
            xmlDoc.async = "false";
            xmlDoc.loadXML(aMessage);

            x = xmlDoc.getElementsByTagName("METHOD");
            var method = x[0].text;
            x = xmlDoc.getElementsByTagName("SID");
            var subId = x[0].text;

            if (method == "PropertyUpdate") {

                x = xmlDoc.getElementsByTagName("e:property");
                for (var i = 0; i < x.length; i++) {
                    var y = x[i].childNodes;
                    if (y.length > 0) {
                        var propertyName = y[0].nodeName;
                        var propertyValue = y[0].text;
                        SetPropertyUpdate(subId, propertyName, propertyValue);
                    }
                }
            }
            else if (method == "SubscriptionTimeout") {

                x = xmlDoc.getElementsByTagName("TIMEOUT");
                if (x) {
                    SetSubscriptionTimeout(subId, x[0].text);
                }
            }
        }
        log("");
    }

    function onSocketError(event) {
        log("*** onSocketError ***");
        log("VAR : event.data :" + event.data);
        log("");
    }

    function onSocketClose() {
        log("*** onSocketClose ***");

        log("VAR : iServices :" + iServices);
        log("");
    }

    function onSocketMessage(event) {
        log("*** onSocketMessage ***");
        log("VAR : event.data :" + event.data);
        ReceiveMessage(event.data);
        log("");
    }

    function onSocketOpen(event) {
        log("*** onSocketOpen ***");

        log("");
    }

    return {
        // Public Variables
        kDefaultSubscriptionTimeoutSeconds: 30,
        kDefaulTimeoutSeconds: 60,
        kRenewTrigger: 0.7,
        kDefaultPort: 54321,


        // Public Methods
        EnableDebugging: function (poll) {
            DEBUG = true;
            if (poll)
                DEBUGPOLL = true;
            log("Debugging Enabled");
        },

        Start: function (aSuccessFunction, aDefaultSubscriptionTimeoutSeconds) {
            log("*** Start ***");
            log("VAR : aDefaultSubscriptionTimeoutSeconds :" + aDefaultSubscriptionTimeoutSeconds);
            kDefaultSubscriptionTimeoutSeconds = aDefaultSubscriptionTimeoutSeconds ? aDefaultSubscriptionTimeoutSeconds : SubscriptionManager.kDefaultSubscriptionTimeoutSeconds;
            log("CALC : aRenewalPollingInterval ? aRenewalPollingInterval : SubscriptionManager.kDefaultPollTimeSeconds :" + (aDefaultSubscriptionTimeoutSeconds ? aDefaultSubscriptionTimeoutSeconds : SubscriptionManager.kDefaultSubscriptionTimeoutSeconds));
            iPort = SubscriptionManager.kDefaultPort;
            log("VAR : SubscriptionManager.kDefaultPort :" + SubscriptionManager.kDefaultPort);
            started = true;
            if ("WebSocket" in window) {
                log("CON : Web Socket Supported");
                socket = new WebSocket("ws://" + window.location.hostname + ":54321/", "upnp:event");
                //socket = new WebSocket("ws://10.2.11.245:54321/", "upnp:event");
                socket.onmessage = onSocketMessage;
                socket.onerror = onSocketError;
                socket.onclose = onSocketClose;
                socket.onopen = aSuccessFunction;
            }
            else {
                log("CON : Web Socket Unsupport");
                alert("Cannot Start Subscription Manager as browser does not support web sockets");
                started = false;
            }
            log("");

        },

        Stop: function () {
            log("*** Stop ***");
            var serviceNames = ServiceNames();
            for (var i = 0; i < serviceNames.length; i++) {
                log("VAR : serviceNames[i] :" + serviceNames[i]);
                log("CALL : RemoveService");
                if (iServices[serviceNames[i]]) {
                    this.RemoveService(iServices[serviceNames[i]].SubscriptionId());
                }
            }
            if (socket) {
                socket.close();
            }
            log("");
        },

        AddService: function (aService, aSuccessFunction) {
            log("*** AddService ***");
            if (started) {
                log("CON : Subscription Manager running");
                var UId = GenerateSubscriptionId();
                aService.SetSubscriptionId(UId);
                log("VAR :  aService.SubscriptionId():" + aService.SubscriptionId());
                iServices[aService.SubscriptionId()] = aService;
                if (aSuccessFunction) {
                    iServices[aService.SubscriptionId()].aSubscribeSuccessFunction = aSuccessFunction;
                }
                log("CALL : SubscribeMessage");
                socket.send(SubscribeMessage(aService, SubscriptionManager.kDefaultSubscriptionTimeoutSeconds));
            }
            else {
                log("CON : Subscription Manager is not running");
                alert("Subscription Manager is not running.  Please ensure 'SubscriptionManager.Start();' has been called prior to subscribing.");
            }
            log("");
        },

        RemoveService: function (aSubscriptionId) {
            log("*** RemoveService ***");
            log("VAR : aSubscriptionId :" + aSubscriptionId);

            if (iServices[aSubscriptionId]) {
                log("CALL : UnsubscribeMessage");
                socket.send(UnsubscribeMessage(aSubscriptionId));
                log("DEL : " + aSubscriptionId);
                delete iServices[aSubscriptionId];
              
                log("CALC : iServices[aSubscriptionId]:" + iServices[aSubscriptionId]);
            }
            else {
                log("NULL : iServices[aSubscriptionId]:" + iServices[aSubscriptionId]);
            }
            log("");
        },

        Port: function () {
            log("*** Port ***");
            log("RET : iPort" + iPort);
            log("");
            return iPort;
        }

    };
})();



var ServiceVariable = function (aName) {
    this.iName = aName;
    this.iValue = null;
    this.iListeners = [];
}

ServiceVariable.prototype.Name = function () {
    return this.iName;
}

ServiceVariable.prototype.Value = function () {
    return this.iValue;
}

ServiceVariable.prototype.SetValue = function (aValue) {
    if (this.iValue != aValue) {
        this.iValue = aValue;
        for (var i = 0; i < this.iListeners.length; i++) {
            try {
                this.iListeners[i].call(this, aValue);
            } catch (e) {
                console.log("Error caught in SetValue: " + e);
            }
        }
    }
}

ServiceVariable.prototype.AddListener = function (aListener) {
    this.iListeners[this.iListeners.length] = aListener;
}


var kEnvelopeStart = '<?xml version="1.0"?>' +
        '<s:Envelope xmlns:s="http://schemas.xmlsoap.org/soap/envelope/">' +
        '<s:Body s:encodingStyle="http://schemas.xmlsoap.org/soap/encoding/"><u:';

var kAjaxTimeout = 10000;

var SoapRequest = function (aAction, aUrl, aDomain, aType, aVersion) {
    this.iAction = aAction;
    this.iUrl = aUrl;
    this.iType = aType;
    this.iVersion = aVersion;
    this.iDomain = aDomain;
    this.iEnvelope = "";
    this.WriteEnvelopeStart(aAction);
}

SoapRequest.prototype.WriteEnvelopeStart = function () {
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

SoapRequest.prototype.WriteEnvelopeEnd = function () {
    this.iEnvelope += "</u:";
    this.iEnvelope += this.iAction;
    this.iEnvelope += "></s:Body></s:Envelope>";
}

SoapRequest.prototype.GetSoapAction = function () {
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

SoapRequest.prototype.CreateAjaxRequest = function (aCallbackFunction, aErrorFunction) {
    var thisObj = this;
    return new jQuery.ajax({
        async: true,
        url: this.iUrl,
        type: "POST",
        dataType: "xml",
        data: this.iEnvelope,
        timeout: 10000,
        success: function (data, textStatus, XMLHttpRequest) {
            if (XMLHttpRequest.status) {
                if (aCallbackFunction) {
                    try {
                        aCallbackFunction(XMLHttpRequest);
                    } catch (e) {
                        console.log("Exception caught in callback" + e.message);
                        if (aErrorFunction) { aErrorFunction(textStatus); };
                    }
                }
            } else {
                console.log("Request has no transport status: " + thisObj.iUrl);
                if (aErrorFunction) { aErrorFunction(textStatus); };
            }
        },
        processData: false,
        error: function (xhr, ajaxOptions, thrownError) {
            if (!aOnError) return;

            aOnError(xhr, ajaxOptions, thrownError);
        },
        beforeSend: function (req) {
            req.setRequestHeader("SOAPAction", thisObj.GetSoapAction());
        },
        contentType: "text/xml; charset=\"utf-8\""
    });
};

SoapRequest.prototype.getElementsByTagNameNS = function (tagName, ns, scope) {
    var elementListForReturn = scope.getElementsByTagName(ns + ":" + tagName);
    if (elementListForReturn.length == 0) {
        elementListForReturn = scope.getElementsByTagName(tagName);
        if (elementListForReturn.length == 0 && document.getElementsByTagNameNS) {
            elementListForReturn = scope.getElementsByTagNameNS(ns, tagName);
        }
    }
    return elementListForReturn;
}

SoapRequest.ReadIntParameter = function (aValue) {
    return aValue * 1;
}

SoapRequest.ReadBoolParameter = function (aValue) {
    return (aValue == "1" || aValue == "true" || aValue == "yes") ? true : false;
}

SoapRequest.ReadStringParameter = function (aValue) {
    return aValue;
}

SoapRequest.ReadBinaryParameter = function (aValue) {
    return atob(aValue);
}

SoapRequest.prototype.WriteIntParameter = function (aTagName, aValue) {
    this.WriteParameter(aTagName, "" + (aValue ? aValue : "0"));
}

SoapRequest.prototype.WriteBoolParameter = function (aTagName, aValue) {
    this.WriteParameter(aTagName, aValue ? "1" : "0");
}

SoapRequest.prototype.WriteStringParameter = function (aTagName, aValue) {
    this.WriteParameter(aTagName, (aValue ? aValue : ""));
}

SoapRequest.prototype.WriteBinaryParameter = function (aTagName, aValue) {
    this.WriteParameter(aTagName, (aValue ? btoa(aValue) : ""));
}

SoapRequest.prototype.WriteParameter = function (aTagName, aValue) {
    this.iEnvelope += "<" + aTagName + ">" + aValue.replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;") + "</" + aTagName + ">";
}

SoapRequest.prototype.GetTransportErrorMessage = function (transport) {
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

SoapRequest.prototype.Send = function (onSuccess, onError) {
    var thisObj = this;
    this.WriteEnvelopeEnd();
    return this.CreateAjaxRequest(
		function (transport) {
		    if (transport.responseXML.getElementsByTagName("faultcode").length > 0) {
		        onError(thisObj.GetTransportErrorMessage(transport), transport);
		    } else {
		        var outParameters = thisObj.getElementsByTagNameNS(thisObj.iAction + "Response", "u", transport.responseXML)[0].childNodes;

		        var result = {};
		        for (var i = 0; i < outParameters.length; i++) {
		            var nodeValue = "";
		            var childNodes = outParameters[i].childNodes;

		            for (var j = 0; j < childNodes.length; j++) {
		                nodeValue += childNodes[j].nodeValue;
		            }
		            result[outParameters[i].nodeName.replace(/.*:/, "")] = (nodeValue != "" ? nodeValue : null);
		         }
		        onSuccess(result);
		    }
		},
		function (transport) {
		    onError(thisObj.GetTransportErrorMessage(transport), transport);
		}
	);
}


$(document).ready(function () {
   // SubscriptionManager.EnableDebugging(false);
   // SubscriptionManager.Start();
});

$(window).unload(function () {
    // subManager.UnsubscribeAll();
    SubscriptionManager.Stop();
    // Close SOcket
});