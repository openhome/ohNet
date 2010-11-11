 

/**
 * Proxy for linn.co.uk:Info:1
 */

var ServiceInfo = function(aUdn){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aUdn + "/linn.co.uk-Info-1/control";
	this.iDomain = "linn.co.uk";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "Info";
	this.iVersion = "1";
	this.iServiceName = "linn.co.uk-Info-1";
	this.iSubscriptionId = "";
	this.iUdn = aUdn;
	
	this.iVariables = {};
			this.iVariables["TrackCount"] = new ServiceVariable("TrackCount");
		this.iVariables["DetailsCount"] = new ServiceVariable("DetailsCount");
		this.iVariables["MetatextCount"] = new ServiceVariable("MetatextCount");
		this.iVariables["Uri"] = new ServiceVariable("Uri");
		this.iVariables["Metadata"] = new ServiceVariable("Metadata");
		this.iVariables["Duration"] = new ServiceVariable("Duration");
		this.iVariables["BitRate"] = new ServiceVariable("BitRate");
		this.iVariables["BitDepth"] = new ServiceVariable("BitDepth");
		this.iVariables["SampleRate"] = new ServiceVariable("SampleRate");
		this.iVariables["Lossless"] = new ServiceVariable("Lossless");
		this.iVariables["CodecName"] = new ServiceVariable("CodecName");
		this.iVariables["Metatext"] = new ServiceVariable("Metatext");
}


ServiceInfo.prototype.TrackCount_Changed = function (aStateChangedFunction) {
    this.Variables().TrackCount.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceInfo.prototype.DetailsCount_Changed = function (aStateChangedFunction) {
    this.Variables().DetailsCount.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceInfo.prototype.MetatextCount_Changed = function (aStateChangedFunction) {
    this.Variables().MetatextCount.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceInfo.prototype.Uri_Changed = function (aStateChangedFunction) {
    this.Variables().Uri.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceInfo.prototype.Metadata_Changed = function (aStateChangedFunction) {
    this.Variables().Metadata.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceInfo.prototype.Duration_Changed = function (aStateChangedFunction) {
    this.Variables().Duration.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceInfo.prototype.BitRate_Changed = function (aStateChangedFunction) {
    this.Variables().BitRate.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceInfo.prototype.BitDepth_Changed = function (aStateChangedFunction) {
    this.Variables().BitDepth.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceInfo.prototype.SampleRate_Changed = function (aStateChangedFunction) {
    this.Variables().SampleRate.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceInfo.prototype.Lossless_Changed = function (aStateChangedFunction) {
    this.Variables().Lossless.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadBoolParameter(state)); 
	});
}
ServiceInfo.prototype.CodecName_Changed = function (aStateChangedFunction) {
    this.Variables().CodecName.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceInfo.prototype.Metatext_Changed = function (aStateChangedFunction) {
    this.Variables().Metatext.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}

ServiceInfo.prototype.ServiceName = function(){
	return this.iServiceName;
}

ServiceInfo.prototype.Variables = function(){
	return this.iVariables;
}

ServiceInfo.prototype.SubscriptionId = function () {
    return this.iSubscriptionId;
}

ServiceInfo.prototype.SetSubscriptionId = function (value) {
    this.iSubscriptionId = value;
}

ServiceInfo.prototype.Udn = function () {
    return this.iUdn;
}

ServiceInfo.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}

ServiceInfo.prototype.Subscribe = function () {
    SubscriptionManager.AddService(this);
}

ServiceInfo.prototype.Unsubscribe = function () {
    SubscriptionManager.RemoveService(this.SubscriptionId());
}


ServiceInfo.prototype.Counters = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Counters", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aTrackCount"] = SoapRequest.ReadIntParameter(result["aTrackCount"]);	
		result["aDetailsCount"] = SoapRequest.ReadIntParameter(result["aDetailsCount"]);	
		result["aMetatextCount"] = SoapRequest.ReadIntParameter(result["aMetatextCount"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceInfo.prototype.Track = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Track", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aUri"] = SoapRequest.ReadStringParameter(result["aUri"]);	
		result["aMetadata"] = SoapRequest.ReadStringParameter(result["aMetadata"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceInfo.prototype.Details = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Details", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aDuration"] = SoapRequest.ReadIntParameter(result["aDuration"]);	
		result["aBitRate"] = SoapRequest.ReadIntParameter(result["aBitRate"]);	
		result["aBitDepth"] = SoapRequest.ReadIntParameter(result["aBitDepth"]);	
		result["aSampleRate"] = SoapRequest.ReadIntParameter(result["aSampleRate"]);	
		result["aLossless"] = SoapRequest.ReadBoolParameter(result["aLossless"]);	
		result["aCodecName"] = SoapRequest.ReadStringParameter(result["aCodecName"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceInfo.prototype.Metatext = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Metatext", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aMetatext"] = SoapRequest.ReadStringParameter(result["aMetatext"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}



