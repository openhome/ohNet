 

/**
 * Proxy for linn.co.uk:Jukebox:1
 */

var ServiceJukebox = function(aId){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aId + "/Jukebox/control";
	this.iDomain = "linn.co.uk";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "Jukebox";
	this.iVersion = "1";
	
	this.iVariables = {};
			this.iVariables["MetaData"] = new ServiceVariable("MetaData");
		this.iVariables["CurrentPreset"] = new ServiceVariable("CurrentPreset");
		this.iVariables["PresetPrefix"] = new ServiceVariable("PresetPrefix");
		this.iVariables["AlbumArtFileName"] = new ServiceVariable("AlbumArtFileName");
}


ServiceJukebox.prototype.ServiceName = function(){
	return this.iType;
}

ServiceJukebox.prototype.Variables = function(){
	return this.iVariables;
}

ServiceJukebox.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}


ServiceJukebox.prototype.SetPresetPrefix = function(aUri, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetPresetPrefix", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("aUri", aUri);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceJukebox.prototype.PresetPrefix = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("PresetPrefix", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aUri"] = request.ReadStringParameter(result["aUri"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceJukebox.prototype.SetAlbumArtFileName = function(aName, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetAlbumArtFileName", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("aName", aName);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceJukebox.prototype.AlbumArtFileName = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("AlbumArtFileName", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aName"] = request.ReadStringParameter(result["aName"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceJukebox.prototype.SetCurrentPreset = function(aPreset, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetCurrentPreset", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aPreset", aPreset);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceJukebox.prototype.CurrentPreset = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("CurrentPreset", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aPreset"] = request.ReadIntParameter(result["aPreset"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceJukebox.prototype.PresetMetaData = function(aPreset, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("PresetMetaData", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aPreset", aPreset);
    request.Send(function(result){
		result["aMetaData"] = request.ReadStringParameter(result["aMetaData"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceJukebox.prototype.LoadManifest = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("LoadManifest", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aTotalPresets"] = request.ReadIntParameter(result["aTotalPresets"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    


