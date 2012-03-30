
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
if (typeof ohnet.util == "undefined" || !ohnet.util) {
    ohnet.util = {};
}



/**
* Contains useful common functions
* @namespace ohnet
* @class util
*/


/**
* A helper method to generate a GUID as a client id
* @method generateGUID
*/
ohnet.util.generateGUID = function () {
	var guid = 'xxxxxxxx-xxxx-4xxx-yxxx-xxxxxxxxxxxx'.replace(/[xy]/g, function (c) {
        var r = Math.random() * 16 | 0, v = c == 'x' ? r : (r & 0x3 | 0x8);
        return v.toString(16);;
    });
	return guid;
};


/**
* A helper method to merge options
* @method extend
* @param {Object} defaults Collection that contains default options
* @param {Object} options Collection that contains user defined options
*/
ohnet.util.mergeOptions = function (defaults,options) {
	var newoptions = {};
	for (var attrname in defaults) { newoptions[attrname] = defaults[attrname]; }
	for (var attrname in options) { newoptions[attrname] = options[attrname]; }
	return newoptions;
};
