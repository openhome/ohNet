 

/**
 * Proxy for zapp.org:TestLights:1
 */

var ServiceTestLights = function(aId){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aId + "/TestLights/control";
	this.iDomain = "zapp.org";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "TestLights";
	this.iVersion = "1";
	
	this.iVariables = {};
			this.iVariables["A_ARG_GetCount_Count"] = new ServiceVariable("A_ARG_GetCount_Count");
		this.iVariables["A_ARG_Index"] = new ServiceVariable("A_ARG_Index");
		this.iVariables["A_ARG_GetRoom_RoomName"] = new ServiceVariable("A_ARG_GetRoom_RoomName");
		this.iVariables["A_ARG_GetName_FriendlyName"] = new ServiceVariable("A_ARG_GetName_FriendlyName");
		this.iVariables["A_ARG_GetPosition_X"] = new ServiceVariable("A_ARG_GetPosition_X");
		this.iVariables["A_ARG_GetPosition_Y"] = new ServiceVariable("A_ARG_GetPosition_Y");
		this.iVariables["A_ARG_GetPosition_Z"] = new ServiceVariable("A_ARG_GetPosition_Z");
		this.iVariables["A_ARG_SetColor_Color"] = new ServiceVariable("A_ARG_SetColor_Color");
		this.iVariables["A_ARG_GetColor_Color"] = new ServiceVariable("A_ARG_GetColor_Color");
		this.iVariables["A_ARG_GetColorComponents_Color"] = new ServiceVariable("A_ARG_GetColorComponents_Color");
		this.iVariables["A_ARG_GetColorComponents_Brightness"] = new ServiceVariable("A_ARG_GetColorComponents_Brightness");
		this.iVariables["A_ARG_GetColorComponents_Red"] = new ServiceVariable("A_ARG_GetColorComponents_Red");
		this.iVariables["A_ARG_GetColorComponents_Green"] = new ServiceVariable("A_ARG_GetColorComponents_Green");
		this.iVariables["A_ARG_GetColorComponents_Blue"] = new ServiceVariable("A_ARG_GetColorComponents_Blue");
}


ServiceTestLights.prototype.ServiceName = function(){
	return this.iType;
}

ServiceTestLights.prototype.Variables = function(){
	return this.iVariables;
}

ServiceTestLights.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}


ServiceTestLights.prototype.GetCount = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetCount", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["Count"] = request.ReadIntParameter(result["Count"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceTestLights.prototype.GetRoom = function(Index, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetRoom", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("Index", Index);
    request.Send(function(result){
		result["RoomName"] = request.ReadStringParameter(result["RoomName"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceTestLights.prototype.GetName = function(Index, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetName", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("Index", Index);
    request.Send(function(result){
		result["FriendlyName"] = request.ReadStringParameter(result["FriendlyName"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceTestLights.prototype.GetPosition = function(Index, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetPosition", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("Index", Index);
    request.Send(function(result){
		result["X"] = request.ReadIntParameter(result["X"]);	
		result["Y"] = request.ReadIntParameter(result["Y"]);	
		result["Z"] = request.ReadIntParameter(result["Z"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceTestLights.prototype.SetColor = function(Index, Color, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetColor", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("Index", Index);
    request.WriteIntParameter("Color", Color);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceTestLights.prototype.GetColor = function(Index, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetColor", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("Index", Index);
    request.Send(function(result){
		result["Color"] = request.ReadIntParameter(result["Color"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceTestLights.prototype.GetColorComponents = function(Color, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetColorComponents", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("Color", Color);
    request.Send(function(result){
		result["Brightness"] = request.ReadIntParameter(result["Brightness"]);	
		result["Red"] = request.ReadIntParameter(result["Red"]);	
		result["Green"] = request.ReadIntParameter(result["Green"]);	
		result["Blue"] = request.ReadIntParameter(result["Blue"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    


