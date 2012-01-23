
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
* A Service Property that can be monitored of state changes
* @namespace ohnet
* @class ServiceProperty
*/
ohnet.serviceproperty = function (name, type) {
    this.name = name; // The name of the property
    this.type = type;
    this.value = null; // The value of the property
    this.listeners = []; // A collection of listeners to notify of property value changes
}

/**
* Sets the value of the property
* @method setValue
* @param {String | Int | Boolean} value The new value for the property
*/
ohnet.serviceproperty.prototype.setValue = function (value) {
    if (this.value != value) {

        switch (this.type) {

            case "int":
                {
                    this.value = ohnet.soaprequest.readIntParameter(value);
                    break;
                }
            case "string":
                {
                    this.value = ohnet.soaprequest.readStringParameter(value);
                    break;
                }
            case "bool":
                {
                    this.value = ohnet.soaprequest.readBoolParameter(value);
                    break;
                }
            case "binary":
                {
                    this.value = ohnet.soaprequest.readBinaryParameter(value);
                    break;
                }
            default:
                {
                    throw "Invalid Property Type: '" + this.type + "'";
                }
        }

       
    }
}

/**
* Notifies all listeners of its value change and calls the event handler
* @method reportChanged
* @param {String | Int | Boolean} value The new value for the property
*/
ohnet.serviceproperty.prototype.reportChanged = function (value) {
    for (var i = this.listeners.length - 1; i > -1; i--) {
            this.listeners[i].call(this, value);
    }
}

/**
* Adds a new event handler function to the listeners for the property
* @method addListener
* @param {Function} listener The event handler function to execute when the property value changes
*/
ohnet.serviceproperty.prototype.addListener = function (listener) {
    this.listeners[this.listeners.length] = listener;
}




