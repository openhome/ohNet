 

/**
 * Proxy for linn.co.uk:Delay:1
 */

var ServiceDelay = function(aUdn){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aUdn + "/linn.co.uk-Delay-1/control";
	this.iDomain = "linn.co.uk";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "Delay";
	this.iVersion = "1";
	this.iServiceName = "linn.co.uk-Delay-1";
	this.iSubscriptionId = "";
	this.iUdn = aUdn;
	
	this.iVariables = {};
			this.iVariables["PresetXml"] = new ServiceVariable("PresetXml");
		this.iVariables["PresetIndex"] = new ServiceVariable("PresetIndex");
		this.iVariables["Visible"] = new ServiceVariable("Visible");
		this.iVariables["Name"] = new ServiceVariable("Name");
		this.iVariables["Delay"] = new ServiceVariable("Delay");
		this.iVariables["Index"] = new ServiceVariable("Index");
		this.iVariables["Uint4"] = new ServiceVariable("Uint4");
}


ServiceDelay.prototype.PresetXml_Changed = function (aStateChangedFunction) {
    this.Variables().PresetXml.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceDelay.prototype.PresetIndex_Changed = function (aStateChangedFunction) {
    this.Variables().PresetIndex.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceDelay.prototype.Visible_Changed = function (aStateChangedFunction) {
    this.Variables().Visible.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadBoolParameter(state)); 
	});
}
ServiceDelay.prototype.Name_Changed = function (aStateChangedFunction) {
    this.Variables().Name.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceDelay.prototype.Delay_Changed = function (aStateChangedFunction) {
    this.Variables().Delay.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceDelay.prototype.Index_Changed = function (aStateChangedFunction) {
    this.Variables().Index.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceDelay.prototype.Uint4_Changed = function (aStateChangedFunction) {
    this.Variables().Uint4.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}

ServiceDelay.prototype.ServiceName = function(){
	return this.iServiceName;
}

ServiceDelay.prototype.Variables = function(){
	return this.iVariables;
}

ServiceDelay.prototype.SubscriptionId = function () {
    return this.iSubscriptionId;
}

ServiceDelay.prototype.SetSubscriptionId = function (value) {
    this.iSubscriptionId = value;
}

ServiceDelay.prototype.Udn = function () {
    return this.iUdn;
}

ServiceDelay.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}

ServiceDelay.prototype.Subscribe = function () {
    SubscriptionManager.AddService(this);
}

ServiceDelay.prototype.Unsubscribe = function () {
    SubscriptionManager.RemoveService(this.SubscriptionId());
}


ServiceDelay.prototype.PresetXml = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("PresetXml", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aPresetXml"] = SoapRequest.ReadStringParameter(result["aPresetXml"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDelay.prototype.PresetIndex = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("PresetIndex", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aIndex"] = SoapRequest.ReadIntParameter(result["aIndex"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDelay.prototype.SetPresetIndex = function(aIndex, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetPresetIndex", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aIndex", aIndex);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDelay.prototype.SetPresetDelay = function(aIndex, aDelay, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetPresetDelay", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aIndex", aIndex);
    request.WriteIntParameter("aDelay", aDelay);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDelay.prototype.SetPresetVisible = function(aIndex, aVisible, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetPresetVisible", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aIndex", aIndex);
    request.WriteBoolParameter("aVisible", aVisible);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDelay.prototype.SetPresetName = function(aIndex, aName, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetPresetName", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aIndex", aIndex);
    request.WriteStringParameter("aName", aName);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDelay.prototype.DelayMinimum = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("DelayMinimum", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aDelay"] = SoapRequest.ReadIntParameter(result["aDelay"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDelay.prototype.DelayMaximum = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("DelayMaximum", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aDelay"] = SoapRequest.ReadIntParameter(result["aDelay"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceDelay.prototype.PresetCount = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("PresetCount", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aCount"] = SoapRequest.ReadIntParameter(result["aCount"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}



