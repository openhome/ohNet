 

/**
 * Proxy for upnp.org:RenderingControl:2
 */

var ServiceRenderingControl = function(aId){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aId + "/RenderingControl/control";
	this.iDomain = "upnp.org";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "RenderingControl";
	this.iVersion = "2";
	
	this.iVariables = {};
			this.iVariables["LastChange"] = new ServiceVariable("LastChange");
		this.iVariables["PresetNameList"] = new ServiceVariable("PresetNameList");
		this.iVariables["Brightness"] = new ServiceVariable("Brightness");
		this.iVariables["Contrast"] = new ServiceVariable("Contrast");
		this.iVariables["Sharpness"] = new ServiceVariable("Sharpness");
		this.iVariables["RedVideoGain"] = new ServiceVariable("RedVideoGain");
		this.iVariables["GreenVideoGain"] = new ServiceVariable("GreenVideoGain");
		this.iVariables["BlueVideoGain"] = new ServiceVariable("BlueVideoGain");
		this.iVariables["RedVideoBlackLevel"] = new ServiceVariable("RedVideoBlackLevel");
		this.iVariables["GreenVideoBlackLevel"] = new ServiceVariable("GreenVideoBlackLevel");
		this.iVariables["BlueVideoBlackLevel"] = new ServiceVariable("BlueVideoBlackLevel");
		this.iVariables["ColorTemperature"] = new ServiceVariable("ColorTemperature");
		this.iVariables["HorizontalKeystone"] = new ServiceVariable("HorizontalKeystone");
		this.iVariables["VerticalKeystone"] = new ServiceVariable("VerticalKeystone");
		this.iVariables["Mute"] = new ServiceVariable("Mute");
		this.iVariables["Volume"] = new ServiceVariable("Volume");
		this.iVariables["VolumeDB"] = new ServiceVariable("VolumeDB");
		this.iVariables["Loudness"] = new ServiceVariable("Loudness");
		this.iVariables["Channel"] = new ServiceVariable("Channel");
		this.iVariables["InstanceID"] = new ServiceVariable("InstanceID");
		this.iVariables["PresetName"] = new ServiceVariable("PresetName");
		this.iVariables["DeviceUDN"] = new ServiceVariable("DeviceUDN");
		this.iVariables["ServiceType"] = new ServiceVariable("ServiceType");
		this.iVariables["ServiceID"] = new ServiceVariable("ServiceID");
		this.iVariables["StateVariableValuePairs"] = new ServiceVariable("StateVariableValuePairs");
		this.iVariables["StateVariableList"] = new ServiceVariable("StateVariableList");
}

ServiceRenderingControl.kChannelMaster = "Master";
ServiceRenderingControl.kPresetNameFactoryDefaults = "FactoryDefaults";

ServiceRenderingControl.prototype.ServiceName = function(){
	return this.iType;
}

ServiceRenderingControl.prototype.Variables = function(){
	return this.iVariables;
}

ServiceRenderingControl.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}


ServiceRenderingControl.prototype.ListPresets = function(InstanceID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("ListPresets", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.Send(function(result){
		result["CurrentPresetNameList"] = request.ReadStringParameter(result["CurrentPresetNameList"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.SelectPreset = function(InstanceID, PresetName, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SelectPreset", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteStringParameter("PresetName", PresetName);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.GetBrightness = function(InstanceID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetBrightness", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.Send(function(result){
		result["CurrentBrightness"] = request.ReadIntParameter(result["CurrentBrightness"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.SetBrightness = function(InstanceID, DesiredBrightness, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetBrightness", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteIntParameter("DesiredBrightness", DesiredBrightness);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.GetContrast = function(InstanceID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetContrast", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.Send(function(result){
		result["CurrentContrast"] = request.ReadIntParameter(result["CurrentContrast"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.SetContrast = function(InstanceID, DesiredContrast, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetContrast", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteIntParameter("DesiredContrast", DesiredContrast);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.GetSharpness = function(InstanceID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetSharpness", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.Send(function(result){
		result["CurrentSharpness"] = request.ReadIntParameter(result["CurrentSharpness"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.SetSharpness = function(InstanceID, DesiredSharpness, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetSharpness", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteIntParameter("DesiredSharpness", DesiredSharpness);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.GetRedVideoGain = function(InstanceID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetRedVideoGain", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.Send(function(result){
		result["CurrentRedVideoGain"] = request.ReadIntParameter(result["CurrentRedVideoGain"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.SetRedVideoGain = function(InstanceID, DesiredRedVideoGain, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetRedVideoGain", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteIntParameter("DesiredRedVideoGain", DesiredRedVideoGain);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.GetGreenVideoGain = function(InstanceID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetGreenVideoGain", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.Send(function(result){
		result["CurrentGreenVideoGain"] = request.ReadIntParameter(result["CurrentGreenVideoGain"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.SetGreenVideoGain = function(InstanceID, DesiredGreenVideoGain, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetGreenVideoGain", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteIntParameter("DesiredGreenVideoGain", DesiredGreenVideoGain);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.GetBlueVideoGain = function(InstanceID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetBlueVideoGain", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.Send(function(result){
		result["CurrentBlueVideoGain"] = request.ReadIntParameter(result["CurrentBlueVideoGain"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.SetBlueVideoGain = function(InstanceID, DesiredBlueVideoGain, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetBlueVideoGain", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteIntParameter("DesiredBlueVideoGain", DesiredBlueVideoGain);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.GetRedVideoBlackLevel = function(InstanceID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetRedVideoBlackLevel", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.Send(function(result){
		result["CurrentRedVideoBlackLevel"] = request.ReadIntParameter(result["CurrentRedVideoBlackLevel"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.SetRedVideoBlackLevel = function(InstanceID, DesiredRedVideoBlackLevel, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetRedVideoBlackLevel", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteIntParameter("DesiredRedVideoBlackLevel", DesiredRedVideoBlackLevel);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.GetGreenVideoBlackLevel = function(InstanceID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetGreenVideoBlackLevel", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.Send(function(result){
		result["CurrentGreenVideoBlackLevel"] = request.ReadIntParameter(result["CurrentGreenVideoBlackLevel"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.SetGreenVideoBlackLevel = function(InstanceID, DesiredGreenVideoBlackLevel, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetGreenVideoBlackLevel", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteIntParameter("DesiredGreenVideoBlackLevel", DesiredGreenVideoBlackLevel);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.GetBlueVideoBlackLevel = function(InstanceID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetBlueVideoBlackLevel", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.Send(function(result){
		result["CurrentBlueVideoBlackLevel"] = request.ReadIntParameter(result["CurrentBlueVideoBlackLevel"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.SetBlueVideoBlackLevel = function(InstanceID, DesiredBlueVideoBlackLevel, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetBlueVideoBlackLevel", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteIntParameter("DesiredBlueVideoBlackLevel", DesiredBlueVideoBlackLevel);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.GetColorTemperature = function(InstanceID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetColorTemperature", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.Send(function(result){
		result["CurrentColorTemperature"] = request.ReadIntParameter(result["CurrentColorTemperature"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.SetColorTemperature = function(InstanceID, DesiredColorTemperature, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetColorTemperature", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteIntParameter("DesiredColorTemperature", DesiredColorTemperature);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.GetHorizontalKeystone = function(InstanceID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetHorizontalKeystone", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.Send(function(result){
		result["CurrentHorizontalKeystone"] = request.ReadIntParameter(result["CurrentHorizontalKeystone"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.SetHorizontalKeystone = function(InstanceID, DesiredHorizontalKeystone, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetHorizontalKeystone", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteIntParameter("DesiredHorizontalKeystone", DesiredHorizontalKeystone);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.GetVerticalKeystone = function(InstanceID, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetVerticalKeystone", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.Send(function(result){
		result["CurrentVerticalKeystone"] = request.ReadIntParameter(result["CurrentVerticalKeystone"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.SetVerticalKeystone = function(InstanceID, DesiredVerticalKeystone, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetVerticalKeystone", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteIntParameter("DesiredVerticalKeystone", DesiredVerticalKeystone);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.GetMute = function(InstanceID, Channel, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetMute", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteStringParameter("Channel", Channel);
    request.Send(function(result){
		result["CurrentMute"] = request.ReadBoolParameter(result["CurrentMute"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.SetMute = function(InstanceID, Channel, DesiredMute, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetMute", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteStringParameter("Channel", Channel);
    request.WriteBoolParameter("DesiredMute", DesiredMute);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.GetVolume = function(InstanceID, Channel, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetVolume", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteStringParameter("Channel", Channel);
    request.Send(function(result){
		result["CurrentVolume"] = request.ReadIntParameter(result["CurrentVolume"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.SetVolume = function(InstanceID, Channel, DesiredVolume, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetVolume", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteStringParameter("Channel", Channel);
    request.WriteIntParameter("DesiredVolume", DesiredVolume);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.GetVolumeDB = function(InstanceID, Channel, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetVolumeDB", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteStringParameter("Channel", Channel);
    request.Send(function(result){
		result["CurrentVolume"] = request.ReadIntParameter(result["CurrentVolume"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.SetVolumeDB = function(InstanceID, Channel, DesiredVolume, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetVolumeDB", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteStringParameter("Channel", Channel);
    request.WriteIntParameter("DesiredVolume", DesiredVolume);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.GetVolumeDBRange = function(InstanceID, Channel, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetVolumeDBRange", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteStringParameter("Channel", Channel);
    request.Send(function(result){
		result["MinValue"] = request.ReadIntParameter(result["MinValue"]);	
		result["MaxValue"] = request.ReadIntParameter(result["MaxValue"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.GetLoudness = function(InstanceID, Channel, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetLoudness", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteStringParameter("Channel", Channel);
    request.Send(function(result){
		result["CurrentLoudness"] = request.ReadBoolParameter(result["CurrentLoudness"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.SetLoudness = function(InstanceID, Channel, DesiredLoudness, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetLoudness", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteStringParameter("Channel", Channel);
    request.WriteBoolParameter("DesiredLoudness", DesiredLoudness);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.GetStateVariables = function(InstanceID, StateVariableList, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetStateVariables", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteStringParameter("StateVariableList", StateVariableList);
    request.Send(function(result){
		result["StateVariableValuePairs"] = request.ReadStringParameter(result["StateVariableValuePairs"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceRenderingControl.prototype.SetStateVariables = function(InstanceID, RenderingControlUDN, ServiceType, ServiceId, StateVariableValuePairs, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetStateVariables", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("InstanceID", InstanceID);
    request.WriteStringParameter("RenderingControlUDN", RenderingControlUDN);
    request.WriteStringParameter("ServiceType", ServiceType);
    request.WriteStringParameter("ServiceId", ServiceId);
    request.WriteStringParameter("StateVariableValuePairs", StateVariableValuePairs);
    request.Send(function(result){
		result["StateVariableList"] = request.ReadStringParameter(result["StateVariableList"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    


