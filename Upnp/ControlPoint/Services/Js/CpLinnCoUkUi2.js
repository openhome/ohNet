 

/**
 * Proxy for linn.co.uk:Ui:2
 */

var ServiceUi = function(aId){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aId + "/Ui/control";
	this.iDomain = "linn.co.uk";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "Ui";
	this.iVersion = "2";
	
	this.iVariables = {};
			this.iVariables["TestPattern"] = new ServiceVariable("TestPattern");
		this.iVariables["TestModeEnabled"] = new ServiceVariable("TestModeEnabled");
		this.iVariables["LightLevel"] = new ServiceVariable("LightLevel");
		this.iVariables["DisplayBrightness"] = new ServiceVariable("DisplayBrightness");
		this.iVariables["DisplayBrightnessAuto"] = new ServiceVariable("DisplayBrightnessAuto");
		this.iVariables["InfraredCommands"] = new ServiceVariable("InfraredCommands");
		this.iVariables["InfraredTerminalCommands"] = new ServiceVariable("InfraredTerminalCommands");
		this.iVariables["DisplayUpsideDown"] = new ServiceVariable("DisplayUpsideDown");
		this.iVariables["DisplayScrollText"] = new ServiceVariable("DisplayScrollText");
		this.iVariables["DisplaySleep"] = new ServiceVariable("DisplaySleep");
		this.iVariables["DisplayLedOff"] = new ServiceVariable("DisplayLedOff");
		this.iVariables["TerminalInputCode"] = new ServiceVariable("TerminalInputCode");
		this.iVariables["TerminalInputName"] = new ServiceVariable("TerminalInputName");
		this.iVariables["DisplayPixels"] = new ServiceVariable("DisplayPixels");
}

ServiceUi.kInfraredCommandsNone = "None";
ServiceUi.kInfraredCommandsAll = "All";
ServiceUi.kInfraredCommandsCd = "Cd";
ServiceUi.kInfraredCommandsDvd = "Dvd";
ServiceUi.kInfraredTerminalCommandsNone = "None";
ServiceUi.kInfraredTerminalCommandsAll = "All";
ServiceUi.kInfraredTerminalCommandsCd = "Cd";
ServiceUi.kInfraredTerminalCommandsDvd = "Dvd";

ServiceUi.prototype.ServiceName = function(){
	return this.iType;
}

ServiceUi.prototype.Variables = function(){
	return this.iVariables;
}

ServiceUi.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}


ServiceUi.prototype.DisplayTestPattern = function(aTestPattern, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("DisplayTestPattern", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aTestPattern", aTestPattern);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceUi.prototype.DisplayFill = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("DisplayFill", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceUi.prototype.DisplayClear = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("DisplayClear", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceUi.prototype.SetTestModeEnabled = function(aEnabled, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetTestModeEnabled", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteBoolParameter("aEnabled", aEnabled);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceUi.prototype.SimulateInfraredInput = function(aCode, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SimulateInfraredInput", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aCode", aCode);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceUi.prototype.SimulateButtonInput = function(aCode, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SimulateButtonInput", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aCode", aCode);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceUi.prototype.SimulateLightSensor = function(aLightLevel, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SimulateLightSensor", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aLightLevel", aLightLevel);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceUi.prototype.GetLightSensorData = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetLightSensorData", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aLightLevel"] = request.ReadIntParameter(result["aLightLevel"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceUi.prototype.SetDisplayBrightness = function(aBrightness, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetDisplayBrightness", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aBrightness", aBrightness);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceUi.prototype.SetDisplayBrightnessAuto = function(aBrightnessAuto, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetDisplayBrightnessAuto", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteBoolParameter("aBrightnessAuto", aBrightnessAuto);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceUi.prototype.SetInfraredCommands = function(aCommands, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetInfraredCommands", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("aCommands", aCommands);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceUi.prototype.InfraredCommands = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("InfraredCommands", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aCommands"] = request.ReadStringParameter(result["aCommands"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceUi.prototype.SetInfraredTerminalCommands = function(aCommands, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetInfraredTerminalCommands", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("aCommands", aCommands);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceUi.prototype.InfraredTerminalCommands = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("InfraredTerminalCommands", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aCommands"] = request.ReadStringParameter(result["aCommands"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceUi.prototype.DisplayBrightness = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("DisplayBrightness", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aBrightness"] = request.ReadIntParameter(result["aBrightness"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceUi.prototype.DisplayBrightnessAuto = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("DisplayBrightnessAuto", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aBrightnessAuto"] = request.ReadBoolParameter(result["aBrightnessAuto"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceUi.prototype.DisplayUpsideDown = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("DisplayUpsideDown", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aUpsideDown"] = request.ReadBoolParameter(result["aUpsideDown"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceUi.prototype.SetDisplayUpsideDown = function(aUpsideDown, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetDisplayUpsideDown", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteBoolParameter("aUpsideDown", aUpsideDown);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceUi.prototype.SetDisplayScrollText = function(aDisplayScrollText, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetDisplayScrollText", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteBoolParameter("aDisplayScrollText", aDisplayScrollText);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceUi.prototype.DisplayScrollText = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("DisplayScrollText", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aDisplayScrollTextEnabled"] = request.ReadBoolParameter(result["aDisplayScrollTextEnabled"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceUi.prototype.SetDisplaySleep = function(aEnabled, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetDisplaySleep", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteBoolParameter("aEnabled", aEnabled);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceUi.prototype.DisplaySleep = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("DisplaySleep", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aEnabled"] = request.ReadBoolParameter(result["aEnabled"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceUi.prototype.SetDisplayLedOff = function(aOff, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetDisplayLedOff", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteBoolParameter("aOff", aOff);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceUi.prototype.DisplayLedOff = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("DisplayLedOff", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aOff"] = request.ReadBoolParameter(result["aOff"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    


