 

/**
* Service Proxy for CpProxyLinnCoUkVolkano1
* @module Zapp
* @class Volkano
*/
	
var CpProxyLinnCoUkVolkano1 = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/linn.co.uk-Volkano-1/control";  // upnp control url
	this.domain = "linn-co-uk";
	this.type = "Volkano";
	this.version = "1";
	this.serviceName = "linn.co.uk-Volkano-1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
CpProxyLinnCoUkVolkano1.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
CpProxyLinnCoUkVolkano1.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}




/**
* A service action to Reboot
* @method Reboot
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkVolkano1.prototype.Reboot = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("Reboot", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to BootMode
* @method BootMode
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkVolkano1.prototype.BootMode = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("BootMode", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aMode"] = Zapp.SoapRequest.readStringParameter(result["aMode"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetBootMode
* @method SetBootMode
* @param {String} aMode An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkVolkano1.prototype.SetBootMode = function(aMode, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetBootMode", this.url, this.domain, this.type, this.version);		
    request.writeStringParameter("aMode", aMode);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to BspType
* @method BspType
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkVolkano1.prototype.BspType = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("BspType", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aBspType"] = Zapp.SoapRequest.readStringParameter(result["aBspType"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to UglyName
* @method UglyName
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkVolkano1.prototype.UglyName = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("UglyName", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aUglyName"] = Zapp.SoapRequest.readStringParameter(result["aUglyName"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to MacAddress
* @method MacAddress
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkVolkano1.prototype.MacAddress = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("MacAddress", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aMacAddress"] = Zapp.SoapRequest.readStringParameter(result["aMacAddress"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to ProductId
* @method ProductId
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkVolkano1.prototype.ProductId = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("ProductId", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aProductNumber"] = Zapp.SoapRequest.readStringParameter(result["aProductNumber"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to BoardId
* @method BoardId
* @param {Int} aIndex An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkVolkano1.prototype.BoardId = function(aIndex, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("BoardId", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aIndex", aIndex);
    request.send(function(result){
		result["aBoardNumber"] = Zapp.SoapRequest.readStringParameter(result["aBoardNumber"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to BoardType
* @method BoardType
* @param {Int} aIndex An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkVolkano1.prototype.BoardType = function(aIndex, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("BoardType", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("aIndex", aIndex);
    request.send(function(result){
		result["aBoardNumber"] = Zapp.SoapRequest.readStringParameter(result["aBoardNumber"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to MaxBoards
* @method MaxBoards
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkVolkano1.prototype.MaxBoards = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("MaxBoards", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aMaxBoards"] = Zapp.SoapRequest.readIntParameter(result["aMaxBoards"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SoftwareVersion
* @method SoftwareVersion
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
CpProxyLinnCoUkVolkano1.prototype.SoftwareVersion = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SoftwareVersion", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["aSoftwareVersion"] = Zapp.SoapRequest.readStringParameter(result["aSoftwareVersion"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



