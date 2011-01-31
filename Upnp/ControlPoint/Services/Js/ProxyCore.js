/**
* The Zapp object is the single global object used by Zapp Services to
* facilitate actions and subscriptions. 
* @module Zapp
* @title Zapp
*/

if (typeof Zapp == "undefined" || !Zapp) {
    /**
    * The Zapp global namespace object.  If Zapp is already defined, the
    * existing Zapp object will not be overwritten so that defined
    * namespaces are preserved.
    * @class Zapp
    * @static
    */
    var Zapp = {};
}

/**
* Manages the subscriptions to the Zapp Services.
* Subscribed services are notified of property state changes.
* @namespace Zapp
* @class SubscriptionManager
* @static
*/
Zapp.SubscriptionManager = (function () {

    // Constants 
    var VERSION = "1.0";
    var DEFAULT_SUBSCRIPTION_TIMEOUT_SEC = 30; // The default suggested timeout in seconds for each subscription.
    var RENEW_TRIGGER = 0.7; // The multiplier in which to send the renewal message. (Send renew message every RENEW_TRIGGER * DEFAULT_SUBSCRIPTION_TIMEOUT_SEC)
    var DEBUG = false; // A flag to enable debugging messages written to console


    // Private Variables
    var services = []; // Collection of Zapp services
    var websocket = null; // HTML 5 web socket object to handle property state events
    var subscriptionCounter = -1; // A unique identifier for each subscription (zero-based).
    var subscriptionTimeoutSec = -1; // The suggested timeout in seconds for each subscription.


    // Public Variables
    var running = false; // A flag to state if the Subscription Manager is running


    // Functions

    /**
    * Generates the next subscription id to identity the subscription
    * @method generateSubscriptionId
    * @return {Int} The next subscription id (Increment)
    */
    var generateSubscriptionId = function () {

        subscriptionCounter = subscriptionCounter + 1;

        if (DEBUG) {
            console.log("generateSubscriptionId/subscriptionCounter: " + subscriptionCounter);
        }

        return subscriptionCounter;
    };


    /**
    * Generates the subscribe message to register the service's subscription
    * @method subscribeMessage
    * @param {Object} service The service interested in subscribing
    * @return {String} The subscribe message to be sent to the Zapp service 
    */
    var subscribeMessage = function (service) {

        var message = "<?xml verison='1.0' ?>";
        message += "<ROOT>";
        message += "<METHOD>Subscribe</METHOD>";
        message += "<UDN>" + service.udn + "</UDN>";
        message += "<SERVICE>" + service.serviceName + "</SERVICE>";
        message += "<SID>" + service.subscriptionId + "</SID>";
        message += "<NT>upnp:event</NT>";
        message += "<TIMEOUT>" + subscriptionTimeoutSec + "</TIMEOUT>";
        message += "</ROOT>";

        if (DEBUG) {
            console.log("subscribeMessage/message: " + message);
        }

        return message;
    };


    /**
    * Generates the Unsubscribe message to unregister the service's subscription
    * @method unsubscribeMessage
    * @param {Int} subscriptionId The subscription id of the service interested in unsubscribing
    * @return {String} The unsubscribe message to be sent to the Zapp service 
    */
    var unsubscribeMessage = function (subscriptionId) {

        var message = "<?xml verison='1.0' ?>";
        message += "<ROOT>";
        message += "<METHOD>Unsubscribe</METHOD>";
        message += "<SID>" + subscriptionId + "</SID>";
        message += "</ROOT>";

        if (DEBUG) {
            console.log("unsubscribeMessage/message: " + message);
        }

        return message;
    };


    /**
    * Generates the Renew message to renew the service's subscription
    * @method renewMessage
    * @param {Int} subscriptionId The subscription id of the service interested in renewing the subscription
    * @return {String} The renew message to be sent to the Zapp service 
    */
    var renewMessage = function (subscriptionId) {

        var message = "<?xml verison='1.0' ?>";
        message += "<ROOT>";
        message += "<METHOD>Renew</METHOD>";
        message += "<SID>" + subscriptionId + "</SID>";
        message += "<TIMEOUT>" + subscriptionTimeoutSec + "</TIMEOUT>";
        message += "</ROOT>";

        if (DEBUG) {
            console.log("renewMessage/message: " + message);
        }

        return message;
    };


    /**
    * Starts the timer to renew subscriptions.  
    * The actual subscription timeout is returned by the Zapp Service. 
    * subscriptionTimeoutSec is the suggested timeout sent to the server.
    * @method setSubscriptionTimeout
    * @param {Int} subscriptionId The subscription id of the service
    * @param {Int} timeoutSeconds The actual subscription timeout
    */
    var setSubscriptionTimeout = function (subscriptionId, timeoutSeconds) {

        var service = services[subscriptionId];
        if (service) {
            var actualSubscriptionTimeoutMs = timeoutSeconds * 1000 * RENEW_TRIGGER;

            var timer = setTimeout(function () {
                renewSubscription(subscriptionId);
            }, actualSubscriptionTimeoutMs);

            service.SubscriptionTimer = timer; // Keep a reference to the timer so we can clear it when the service unsubscribes

            if (DEBUG) {
                console.log("setSubscriptionTimeout/actualSubscriptionTimeoutMs:" + actualSubscriptionTimeoutMs);
            }
        }
        else {
            if (DEBUG) {
                console.log("setSubscriptionTimeout/service: NULL");
            }
        }
    };


    /**
    * Calls SetValue of the property to notify listeners
    * @method setPropertyUpdate
    * @param {Int} subscriptionId The subscription id of the service
    * @param {String} propertyName The property name to update
    * @param {String} propertyValue The new value of the property
    */
    var setPropertyUpdate = function (subscriptionId, propertyName, propertyValue) {

        var service = services[subscriptionId];
        if (service) {
            var property = service.serviceProperties[propertyName];
            if (property) {
                property.setValue(propertyValue);
                if (DEBUG) {
                    console.log("setPropertyUpdate/aSubscriptionId: " + subscriptionId);
                    console.log("setPropertyUpdate/propertyName: " + propertyName);
                    console.log("setPropertyUpdate/propertyValue: " + propertyValue);
                }
            }
            else {
                if (DEBUG) {
                    console.log("setPropertyUpdate/service: NULL");
                }
            }
        }
        else {
            if (DEBUG) {
                console.log("setPropertyUpdate/service: NULL");
            }
        }
    };


    /**
    * Sends a renew socket message to renew the subscription
    * @method renewSubscription
    * @param {Int} subscriptionId The subscription id of the service
    */
    var renewSubscription = function (subscriptionId) {

        var service = services[subscriptionId];
        if (service) {
            if (service.SubscriptionTimer) {
                websocket.send(renewMessage(subscriptionId));
                if (DEBUG) {
                    console.log("renewSubscription/subscriptionId: " + subscriptionId);
                }
            }
            else {
                if (DEBUG) {
                    console.log("renewSubscription/service.SubscriptionTimer: NULL");
                }
            }
        }
        else {
            if (DEBUG) {
                console.log("renewSubscription/service: NULL");
            }
        }
    };

    /**
    * Parses the XML message recieved from the Zapp Service
    * @method receiveMessage
    * @param {String} message The XML message
    */
    var receiveMessage = function (message) {
        if (window.DOMParser) { // NON-IE
            parser = new DOMParser();
            xmlDoc = parser.parseFromString(message, "text/xml");

            var methodNode = xmlDoc.getElementsByTagNameNS("*", "METHOD"); // NON-IE
            var method = methodNode[0].textContent;

            var subscriptionIdNode = xmlDoc.getElementsByTagNameNS("*", "SID"); // NON-IE
            var subscriptionId = subscriptionIdNode[0].textContent;

            if (DEBUG) {
                console.log("receiveMessage/method: " + method);
            }

            if (method == "PropertyUpdate") {
                receivePropertyUpdate(subscriptionId, xmlDoc);
            }
            else if (method == "SubscriptionTimeout") {
                receiveSubscriptionTimeout(subscriptionId, xmlDoc);
            }
        }
        else {
            alert("Zapp.SubscriptionManager: Cannot parse subscription message as browser does not support it.");
            if (DEBUG) {
                console.log("receiveMessage/window.DOMParser: NULL");
            }
        }
    };


    /**
    * Traveres the XML object to extract the property updates
    * @method receivePropertyUpdate
    * @param {Int} subscriptionId The subscription id of the service
    * @param {Object} xmlDoc The XML to traverse
    */
    var receivePropertyUpdate = function (subscriptionId, xmlDoc) {

        var properties = xmlDoc.getElementsByTagNameNS("*", "property"); // NON-IE
        if (properties) {
            for (var i = properties.length - 1; i > -1; i--) {
                var property = properties[i].childNodes[0];
                if (property) {
                    setPropertyUpdate(subscriptionId, property.tagName, property.textContent);
                    if (DEBUG) {
                        console.log("receivePropertyUpdate/subscriptionId: " + subscriptionId);
                        console.log("receivePropertyUpdate/property.tagName: " + property.tagName);
                        console.log("receivePropertyUpdate/property.textContent: " + property.textContent);
                    }
                }
                else {
                    if (DEBUG) {
                        console.log("receivePropertyUpdate/property: NULL");
                    }
                }
            }
        }
        else {
            if (DEBUG) {
                console.log("receivePropertyUpdate/properties: NULL");
            }
        }

    };

    /**
    * Traveres the XML object to extract the subscription timeout
    * @method receiveSubscriptionTimeout
    * @param {Int} subscriptionId The subscription id of the service
    * @param {Object} xmlDoc The XML to traverse
    */
    var receiveSubscriptionTimeout = function (subscriptionId, xmlDoc) {

        var timeoutNode = xmlDoc.getElementsByTagNameNS("*", "TIMEOUT");
        if (timeoutNode) {
            var timeout = timeoutNode[0].textContent;
            if (timeout) {
                var service = services[subscriptionId];

                if (service.serviceAddedFunction) {
                    service.serviceAddedFunction();
                    service.serviceAddedFunction = null;
                }
                setSubscriptionTimeout(subscriptionId, timeout);

                if (DEBUG) {
                    console.log("receiveSubscriptionTimeout/subscriptionId: " + subscriptionId);
                    console.log("receiveSubscriptionTimeout/timeout: " + timeout);
                }
            }
            else {
                if (DEBUG) {
                    console.log("receiveSubscriptionTimeout/timeoutNode: NULL");
                }
            }
        }
        else {
            if (DEBUG) {
                console.log("receiveSubscriptionTimeout/timeouts: NULL");
            }
        }

    };


    /**
    * Socket event for when an error occurs.  Debugging purposes only.
    * @method onSocketError
    */
    var onSocketError = function () {
        if (DEBUG) {
            console.log("onSocketError");
        }
    };


    /**
    * Socket event for when the socket is closed.  Debugging purposes only.
    * @method onSocketClose
    */
    var onSocketClose = function () {
        if (DEBUG) {
            console.log("onSocketClose");
        }
    };

    /**
    * Socket event for when the socket is opened.  Debugging purposes only.
    * @method onSocketOpen
    */
    var onSocketOpen = function () {
        if (DEBUG) {
            console.log("onSocketOpen");
        }
    };

    /**
    * Socket event for when a message is recieved.
    * @method onSocketMessage
    * @param {Object} event The data received
    */
    var onSocketMessage = function (event) {
        receiveMessage(event.data);

        if (DEBUG) {
            console.log("onSocketMessage/event.data: " + event.data);
        }
    };


    /**
    * Starts the Subscription Manager and opens a Web Socket.
    * @method start
    * @param {Function} startedFunction The function to call once the Subscription Manager successfully starts.
    * @param {Boolean} debugMode A switch to turn debugging on to log debugging messages to console.
    * @param {Int} subscriptionTimeoutSeconds The suggested subscription timeout value.  Overrides the default.
    */
    var start = function (startedFunction, debugMode, subscriptionTimeoutSeconds) {

        if (debugMode) {
            DEBUG = debugMode;
            console.log("*** Zapp.SubscriptionManager v" + VERSION + " ***");
        }

        subscriptionTimeoutSec = subscriptionTimeoutSeconds ? subscriptionTimeoutSeconds : DEFAULT_SUBSCRIPTION_TIMEOUT_SEC;
        var websocketSupported = ("WebSocket" in window);
        if (websocketSupported) { // NON-IE check if Websockets is supported
            var websocketServerLocation = "ws://" + window.location.hostname + ":54321/";
            websocket = new WebSocket(websocketServerLocation, "upnp:event"); // TODO : Needs to acquire the port

            if (DEBUG) {
                console.log("start/websocketServerLocation: " + websocketServerLocation);
            }

            websocket.onmessage = onSocketMessage;
            websocket.onerror = onSocketError;
            websocket.onclose = onSocketClose;
            websocket.onopen = startedFunction;
        }
        else {
            if (DEBUG) {
                console.log("start/websocketSupported: NULL");
            }
            alert("Zapp.SubscriptionManager: Cannot start Subscription Manager as browser does not support web sockets.");
            running = false;
        }

        running = true;
    };


    /**
    * Stops the Subscription Manager and removes all services
    * @method stop
    */
    var stop = function () {
        for (var i = services.length - 1; i > -1; i--) {
            var service = services[i];
            if (service) {

                if (DEBUG) {
                    console.log("stop/service.subscriptionId: " + service.subscriptionId);
                }

                this.RemoveService(service.subscriptionId);
            }
            else {
                if (DEBUG) {
                    console.log("stop/service: NULL");
                }
            }
        }
        if (websocket) {
            websocket.close();
        }
    };

    /**
    * Adds a new service to the Services collection and subscribes for property changes
    * @method addService
    * @param {Object} service The Service to be added
    * @param {Function} serviceAddedFunction The function to call once the service has been successfully added
    */
    var addService = function (service, serviceAddedFunction) {

        if (running) {

            var uId = generateSubscriptionId();
            service.subscriptionId = uId;
            services[uId] = service;

            if (serviceAddedFunction) {
                service.serviceAddedFunction = serviceAddedFunction;
            }
            websocket.send(subscribeMessage(service));
            if (DEBUG) {
                console.log("addService/service.subscriptionId : " + service.subscriptionId);
            }
        }
        else {
            if (DEBUG) {
                console.log("addService/running: false");
            }
            alert("Subscription Manager is not running.  Please ensure 'Zapp.SubscriptionManager.start();' has been called prior to subscribing.");
        }
    };

    /**
    * Removes a service from the Services collection and unsubscribes
    * @method removeService
    * @param {Int} subscriptionId The subscription id of the service
    */
    var removeService = function (subscriptionId) {
        var service = services[subscriptionId];

        if (service) {

            websocket.send(unsubscribeMessage(subscriptionId));

            if (service.SubscriptionTimer) { // Stop in-progress timers
                clearTimeout(service.SubscriptionTimer);
            }
            delete services[subscriptionId];

            if (DEBUG) {
                console.log("removeService\services[aSubscriptionId] (Should be null): " + services[subscriptionId]);
            }
        }
        else {
            if (DEBUG) {
                console.log("removeService\service: NULL");
            }
        }
    };

    return {
        // Public Variables
        running: running,

        // Public Methods
        start: start,
        stop: stop,
        addService: addService,
        removeService: removeService
    };
})();




/**
* A Service Property that can be monitored of state changes
* @namespace Zapp
* @class ServiceProperty
*/
Zapp.ServiceProperty = function (name) {
    this.name = name; // The name of the property
    this.value = null; // The value of the property
    this.listeners = []; // A collection of listeners to notify of property value changes
}

/**
* Notifies all listeners of its value change and calls the event handler
* @method setValue
* @param {String | Int | Boolean} value The new value for the property
*/
Zapp.ServiceProperty.prototype.setValue = function (value) {
    if (this.value != value) {
        this.value = value;
        for (var i = this.listeners.length - 1; i > -1; i--) {
            try {
                this.listeners[i].call(this, value);

            } catch (e) {
                console.log("setValue: " + e);
            }
        }
    }
}

/**
* Adds a new event handler function to the listeners for the property
* @method addListener
* @param {Function} listener The event handler function to execute when the property value changes
*/
Zapp.ServiceProperty.prototype.addListener = function (listener) {
    this.listeners[this.listeners.length] = listener;
}




/**
* A wrapper for sending and receiving soap messages via jQuery ajax
* @namespace Zapp
* @class SoapRequest
*/

Zapp.SoapRequest = function (action, url, domain, type, version) {
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
Zapp.SoapRequest.prototype.writeEnvelopeStart = function () {
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
Zapp.SoapRequest.prototype.writeEnvelopeEnd = function () {
    this.envelope += "</u:";
    this.envelope += this.action;
    this.envelope += "></s:Body></s:Envelope>";
}


/**
* Builds the action of the soap message
* @method getSoapAction
*/
Zapp.SoapRequest.prototype.getSoapAction = function () {
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
Zapp.SoapRequest.prototype.send = function (successFunction, errorFunction) {
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
* A wrapper of the jQuery ajax request
* @method createAjaxRequest
* @param {Function} successFunction The function to execute once the ajax request returns
* @param {Function} errorFunction The function to execute if an error occurs in the ajax request
*/
Zapp.SoapRequest.prototype.createAjaxRequest = function (successFunction, errorFunction) {
    var _this = this;
    YUI().use("io-base", function (Y) {
        var cfg = {
            method: "POST",
            data: _this.envelope,
            headers: { 'SOAPAction': _this.getSoapAction() },
            xdr: {
                dataType: 'text/xml; charset=\"utf-8\"'
            }
        };

        Y.io(_this.url, cfg);

        Y.on('io:success', onSuccess, Y, true);
        Y.on('io:failure', onFailure, Y, 'Transaction Failed');

        function onSuccess(transactionid, response, arguments) {
            // transactionid : The transaction's ID.
            // response: The response object.
            // arguments: Boolean value "true".
            if (response.status) {
                if (successFunction) {
                    try {
                        successFunction(response);
                    } catch (e) {
                        console.log("createAjaxRequest: " + e.message);
                        if (errorFunction) { errorFunction(textStatus); };
                    }
                }
            } else {
                console.log("createAjaxRequest: " + _this.url);
                if (errorFunction) { errorFunction(); };
            }
        }

        function onFailure(transactionid, response, arguments) {
            // transactionid : The transaction's ID.
            // response: The response object.  Only status and 
            //           statusText are populated when the 
            //           transaction is terminated due to abort 
            //           or timeout.  The status will read
            //           0, and statusText will return "timeout" 
            //           or "abort" depending on the mode of 
            //           termination.
            // arguments: String "Transaction Failed".
            if (errorFunction) {
                errorFunction(response);
            }
        }
    });

    //    var _this = this;

    //    var parameters = this.envelope;
    //    var headers =
    //[
    //{ name: "SOAPAction", value: _this.getSoapAction()
    //}]
    //    var xhr = new wink.XhrSOAP();

    //    xhr.sendData(this.url, parameters, 'POST', { method: 'onsuccess' }, { method: 'onfailure' }, headers);

    //    onsuccess = function (data, textStatus, XMLHttpRequest) {
    //        if (XMLHttpRequest.status) {
    //            if (successFunction) {
    //                try {
    //                    successFunction(XMLHttpRequest);
    //                } catch (e) {
    //                    console.log("createAjaxRequest: " + e.message);
    //                    if (errorFunction) { errorFunction(textStatus); };
    //                }
    //            }
    //        } else {
    //            console.log("createAjaxRequest: " + _this.url);
    //            if (errorFunction) { errorFunction(); };
    //        }
    //    }

    //    onfailure = function (XMLHttpRequest, textStatus, errorThrown) {
    //        if (errorFunction) {
    //            errorFunction(XMLHttpRequest);
    //        }
    //    }
    //    return xhr;

    //    return new jQuery.ajax({
    //        async: true,
    //        url: this.url,
    //        type: "POST",
    //        dataType: "xml",
    //        data: this.envelope,
    //        success: function (data, textStatus, XMLHttpRequest) {
    //            if (XMLHttpRequest.status) {
    //                if (successFunction) {
    //                    try {
    //                        successFunction(XMLHttpRequest);
    //                    } catch (e) {
    //                        console.log("createAjaxRequest: " + e.message);
    //                        if (errorFunction) { errorFunction(textStatus); };
    //                    }
    //                }
    //            } else {
    //                console.log("createAjaxRequest: " + _this.url);
    //                if (errorFunction) { errorFunction(); };
    //            }
    //        },
    //        processData: false,
    //        error: function (XMLHttpRequest, textStatus, errorThrown) {
    //            if (errorFunction) {
    //                errorFunction(XMLHttpRequest);
    //            }

    //        },
    //        beforeSend: function (req) {
    //            req.setRequestHeader("SOAPAction", _this.getSoapAction());
    //        },
    //        contentType: "text/xml; charset=\"utf-8\""
    //    });
};


/**
* Provides a default error handler to output the error to console
* @method defaultErrorFunction
* @param {Object} XMLHttpRequest The XMLHTTPRequest
* @param {String} textStatus The error type
* @param {Object} errorThrown The exception object if applicable
*/
Zapp.SoapRequest.prototype.defaultErrorFunction = function (XMLHttpRequest, textStatus, errorThrown) {
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
Zapp.SoapRequest.prototype.getTransportErrorMessage = function (transport) {
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
Zapp.SoapRequest.readIntParameter = function (value) {
    return value * 1;
}

/**
* Helper to Read an Bool
* @method readBoolParameter
* @param {String} value The value to be read as a Boolean
* @static
* @return {Boolean} The boolean value
*/
Zapp.SoapRequest.readBoolParameter = function (value) {
    return (value == "1" || value == "true" || value == "yes") ? true : false;
}

/**
* Helper to Read a String
* @method readStringParameter
* @param {String} value The value to be read as a String (no logic required)
* @static
* @return {String} The string value
*/
Zapp.SoapRequest.readStringParameter = function (value) {
    return value;
}

/**
* Helper to Read a Binary
* @method readBinaryParameter
* @param {String} value The value to be read as a String (no logic required)
* @static
* @return {String} The binary value converted from base64
*/
Zapp.SoapRequest.readBinaryParameter = function (value) {
    return atob(value); // NON-IE
}

/**
* Helper to write an Integer into a xml tag
* @method writeIntParameter
* @param {String} tagName The xml tag name to be inserted into the SOAP envelope
* @param {String} value The xml tag value to be inserted into the SOAP envelope
*/
Zapp.SoapRequest.prototype.writeIntParameter = function (tagName, value) {
    this.writeParameter(tagName, "" + (value ? value : "0"));
}

/**
* Helper to write a Boolean into a xml tag
* @method writeBoolParameter
* @param {String} tagName The xml tag name to be inserted into the SOAP envelope
* @param {String} value The xml tag value to be inserted into the SOAP envelope
*/
Zapp.SoapRequest.prototype.writeBoolParameter = function (tagName, value) {
    this.writeParameter(tagName, value ? "1" : "0");
}

/**
* Helper to write a String into a xml tag
* @method writeBoolParameter
* @param {String} tagName The xml tag name to be inserted into the SOAP envelope
* @param {String} value The xml tag value to be inserted into the SOAP envelope
*/
Zapp.SoapRequest.prototype.writeStringParameter = function (tagName, value) {
    this.writeParameter(tagName, (value ? value : ""));
}

/**
* Helper to write Binary into a xml tag
* @method writeBinaryParameter
* @param {String} tagName The xml tag name to be inserted into the SOAP envelope
* @param {String} value The xml tag value to be inserted into the SOAP envelope
*/
Zapp.SoapRequest.prototype.writeBinaryParameter = function (tagName, value) {
    this.writeParameter(tagName, (value ? btoa(value) : ""));
}

/**
* Helper to format the tag and value into a xml tag and insert into the SOAP enveloper
* @method writeParameter
* @param {String} tagName The xml tag name to be inserted into the SOAP envelope
* @param {String} value The xml tag value to be inserted into the SOAP envelope
*/
Zapp.SoapRequest.prototype.writeParameter = function (tagName, value) {
    this.envelope += "<" + tagName + ">" + value.replace(/&/g, "&amp;").replace(/</g, "&lt;").replace(/>/g, "&gt;") + "</" + tagName + ">";
}
