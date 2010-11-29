 

/**
* Service Proxy for zapp.org:TestLights:1
* @module Zapp
* @class TestLights
*/

var ServiceTestLights = function(udn){	

	this.url = window.location.protocol + "//" + window.location.host + "/" + udn + "/zapp.org-TestLights-1/control";  // upnp control url
	this.domain = "zapp.org";
	if (this.domain == "upnp.org") {
		this.domain = "schemas.upnp.org";
    }
	this.domain = this.domain.replace(/\./,"-");
	this.type = "TestLights";
	this.version = "1";
	this.serviceName = "zapp.org-TestLights-1";
	this.subscriptionId = "";  // Subscription identifier unique to each Subscription Manager 
	this.udn = udn;   // device name
	
	// Collection of service properties
	this.serviceProperties = {};
	this.serviceProperties["A_ARG_GetCount_Count"] = new Zapp.ServiceProperty("A_ARG_GetCount_Count");
	this.serviceProperties["A_ARG_Index"] = new Zapp.ServiceProperty("A_ARG_Index");
	this.serviceProperties["A_ARG_GetRoom_RoomName"] = new Zapp.ServiceProperty("A_ARG_GetRoom_RoomName");
	this.serviceProperties["A_ARG_GetName_FriendlyName"] = new Zapp.ServiceProperty("A_ARG_GetName_FriendlyName");
	this.serviceProperties["A_ARG_GetPosition_X"] = new Zapp.ServiceProperty("A_ARG_GetPosition_X");
	this.serviceProperties["A_ARG_GetPosition_Y"] = new Zapp.ServiceProperty("A_ARG_GetPosition_Y");
	this.serviceProperties["A_ARG_GetPosition_Z"] = new Zapp.ServiceProperty("A_ARG_GetPosition_Z");
	this.serviceProperties["A_ARG_SetColor_Color"] = new Zapp.ServiceProperty("A_ARG_SetColor_Color");
	this.serviceProperties["A_ARG_GetColor_Color"] = new Zapp.ServiceProperty("A_ARG_GetColor_Color");
	this.serviceProperties["A_ARG_GetColorComponents_Color"] = new Zapp.ServiceProperty("A_ARG_GetColorComponents_Color");
	this.serviceProperties["A_ARG_GetColorComponents_Brightness"] = new Zapp.ServiceProperty("A_ARG_GetColorComponents_Brightness");
	this.serviceProperties["A_ARG_GetColorComponents_Red"] = new Zapp.ServiceProperty("A_ARG_GetColorComponents_Red");
	this.serviceProperties["A_ARG_GetColorComponents_Green"] = new Zapp.ServiceProperty("A_ARG_GetColorComponents_Green");
	this.serviceProperties["A_ARG_GetColorComponents_Blue"] = new Zapp.ServiceProperty("A_ARG_GetColorComponents_Blue");
}



/**
* Subscribes the service to the subscription manager to listen for property change events
* @method Subscribe
* @param {Function} serviceAddedFunction The function that executes once the subscription is successful
*/
ServiceTestLights.prototype.subscribe = function (serviceAddedFunction) {
    Zapp.SubscriptionManager.addService(this,serviceAddedFunction);
}


/**
* Unsubscribes the service from the subscription manager to stop listening for property change events
* @method Unsubscribe
*/
ServiceTestLights.prototype.unsubscribe = function () {
    Zapp.SubscriptionManager.removeService(this.subscriptionId);
}




/**
* Adds a listener to handle "A_ARG_GetCount_Count" property change events
* @method A_ARG_GetCount_Count_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestLights.prototype.A_ARG_GetCount_Count_Changed = function (stateChangedFunction) {
    this.serviceProperties.A_ARG_GetCount_Count.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "A_ARG_Index" property change events
* @method A_ARG_Index_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestLights.prototype.A_ARG_Index_Changed = function (stateChangedFunction) {
    this.serviceProperties.A_ARG_Index.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "A_ARG_GetRoom_RoomName" property change events
* @method A_ARG_GetRoom_RoomName_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestLights.prototype.A_ARG_GetRoom_RoomName_Changed = function (stateChangedFunction) {
    this.serviceProperties.A_ARG_GetRoom_RoomName.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "A_ARG_GetName_FriendlyName" property change events
* @method A_ARG_GetName_FriendlyName_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestLights.prototype.A_ARG_GetName_FriendlyName_Changed = function (stateChangedFunction) {
    this.serviceProperties.A_ARG_GetName_FriendlyName.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readStringParameter(state)); 
	});
}


/**
* Adds a listener to handle "A_ARG_GetPosition_X" property change events
* @method A_ARG_GetPosition_X_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestLights.prototype.A_ARG_GetPosition_X_Changed = function (stateChangedFunction) {
    this.serviceProperties.A_ARG_GetPosition_X.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "A_ARG_GetPosition_Y" property change events
* @method A_ARG_GetPosition_Y_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestLights.prototype.A_ARG_GetPosition_Y_Changed = function (stateChangedFunction) {
    this.serviceProperties.A_ARG_GetPosition_Y.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "A_ARG_GetPosition_Z" property change events
* @method A_ARG_GetPosition_Z_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestLights.prototype.A_ARG_GetPosition_Z_Changed = function (stateChangedFunction) {
    this.serviceProperties.A_ARG_GetPosition_Z.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "A_ARG_SetColor_Color" property change events
* @method A_ARG_SetColor_Color_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestLights.prototype.A_ARG_SetColor_Color_Changed = function (stateChangedFunction) {
    this.serviceProperties.A_ARG_SetColor_Color.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "A_ARG_GetColor_Color" property change events
* @method A_ARG_GetColor_Color_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestLights.prototype.A_ARG_GetColor_Color_Changed = function (stateChangedFunction) {
    this.serviceProperties.A_ARG_GetColor_Color.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "A_ARG_GetColorComponents_Color" property change events
* @method A_ARG_GetColorComponents_Color_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestLights.prototype.A_ARG_GetColorComponents_Color_Changed = function (stateChangedFunction) {
    this.serviceProperties.A_ARG_GetColorComponents_Color.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "A_ARG_GetColorComponents_Brightness" property change events
* @method A_ARG_GetColorComponents_Brightness_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestLights.prototype.A_ARG_GetColorComponents_Brightness_Changed = function (stateChangedFunction) {
    this.serviceProperties.A_ARG_GetColorComponents_Brightness.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "A_ARG_GetColorComponents_Red" property change events
* @method A_ARG_GetColorComponents_Red_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestLights.prototype.A_ARG_GetColorComponents_Red_Changed = function (stateChangedFunction) {
    this.serviceProperties.A_ARG_GetColorComponents_Red.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "A_ARG_GetColorComponents_Green" property change events
* @method A_ARG_GetColorComponents_Green_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestLights.prototype.A_ARG_GetColorComponents_Green_Changed = function (stateChangedFunction) {
    this.serviceProperties.A_ARG_GetColorComponents_Green.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* Adds a listener to handle "A_ARG_GetColorComponents_Blue" property change events
* @method A_ARG_GetColorComponents_Blue_Changed
* @param {Function} stateChangedFunction The handler for state changes
*/
ServiceTestLights.prototype.A_ARG_GetColorComponents_Blue_Changed = function (stateChangedFunction) {
    this.serviceProperties.A_ARG_GetColorComponents_Blue.addListener(function (state) 
	{ 
		stateChangedFunction(Zapp.SoapRequest.readIntParameter(state)); 
	});
}


/**
* A service action to GetCount
* @method GetCount
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceTestLights.prototype.GetCount = function(successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetCount", this.url, this.domain, this.type, this.version);		
    request.send(function(result){
		result["Count"] = Zapp.SoapRequest.readIntParameter(result["Count"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetRoom
* @method GetRoom
* @param {Int} Index An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceTestLights.prototype.GetRoom = function(Index, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetRoom", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("Index", Index);
    request.send(function(result){
		result["RoomName"] = Zapp.SoapRequest.readStringParameter(result["RoomName"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetName
* @method GetName
* @param {Int} Index An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceTestLights.prototype.GetName = function(Index, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetName", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("Index", Index);
    request.send(function(result){
		result["FriendlyName"] = Zapp.SoapRequest.readStringParameter(result["FriendlyName"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetPosition
* @method GetPosition
* @param {Int} Index An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceTestLights.prototype.GetPosition = function(Index, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetPosition", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("Index", Index);
    request.send(function(result){
		result["X"] = Zapp.SoapRequest.readIntParameter(result["X"]);	
		result["Y"] = Zapp.SoapRequest.readIntParameter(result["Y"]);	
		result["Z"] = Zapp.SoapRequest.readIntParameter(result["Z"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to SetColor
* @method SetColor
* @param {Int} Index An action parameter
* @param {Int} Color An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceTestLights.prototype.SetColor = function(Index, Color, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("SetColor", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("Index", Index);
    request.writeIntParameter("Color", Color);
    request.send(function(result){
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetColor
* @method GetColor
* @param {Int} Index An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceTestLights.prototype.GetColor = function(Index, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetColor", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("Index", Index);
    request.send(function(result){
		result["Color"] = Zapp.SoapRequest.readIntParameter(result["Color"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}


/**
* A service action to GetColorComponents
* @method GetColorComponents
* @param {Int} Color An action parameter
* @param {Function} successFunction The function that is executed when the action has completed successfully
* @param {Function} errorFunction The function that is executed when the action has cause an error
*/
ServiceTestLights.prototype.GetColorComponents = function(Color, successFunction, errorFunction){	
	var request = new Zapp.SoapRequest("GetColorComponents", this.url, this.domain, this.type, this.version);		
    request.writeIntParameter("Color", Color);
    request.send(function(result){
		result["Brightness"] = Zapp.SoapRequest.readIntParameter(result["Brightness"]);	
		result["Red"] = Zapp.SoapRequest.readIntParameter(result["Red"]);	
		result["Green"] = Zapp.SoapRequest.readIntParameter(result["Green"]);	
		result["Blue"] = Zapp.SoapRequest.readIntParameter(result["Blue"]);	
	
		if (successFunction){
			successFunction(result);
		}
	}, function(message, transport) {
		if (errorFunction) {errorFunction(message, transport);}
	});
}



