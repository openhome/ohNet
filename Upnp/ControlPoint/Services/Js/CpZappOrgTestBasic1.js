 

/**
 * Proxy for zapp.org:TestBasic:1
 */

var ServiceTestBasic = function(aUdn){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aUdn + "/zapp.org-TestBasic-1/control";
	this.iDomain = "zapp.org";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "TestBasic";
	this.iVersion = "1";
	this.iServiceName = "zapp.org-TestBasic-1";
	this.iSubscriptionId = "";
	this.iUdn = aUdn;
	
	this.iVariables = {};
			this.iVariables["A_ARG_Increment_Value"] = new ServiceVariable("A_ARG_Increment_Value");
		this.iVariables["A_ARG_Increment_Result"] = new ServiceVariable("A_ARG_Increment_Result");
		this.iVariables["A_ARG_Decrement_Value"] = new ServiceVariable("A_ARG_Decrement_Value");
		this.iVariables["A_ARG_Decrement_Result"] = new ServiceVariable("A_ARG_Decrement_Result");
		this.iVariables["A_ARG_Toggle_Value"] = new ServiceVariable("A_ARG_Toggle_Value");
		this.iVariables["A_ARG_Toggle_Result"] = new ServiceVariable("A_ARG_Toggle_Result");
		this.iVariables["A_ARG_EchoString_Value"] = new ServiceVariable("A_ARG_EchoString_Value");
		this.iVariables["A_ARG_EchoString_Result"] = new ServiceVariable("A_ARG_EchoString_Result");
		this.iVariables["A_ARG_EchoBinary_Value"] = new ServiceVariable("A_ARG_EchoBinary_Value");
		this.iVariables["A_ARG_EchoBinary_Result"] = new ServiceVariable("A_ARG_EchoBinary_Result");
		this.iVariables["VarUint"] = new ServiceVariable("VarUint");
		this.iVariables["VarInt"] = new ServiceVariable("VarInt");
		this.iVariables["VarBool"] = new ServiceVariable("VarBool");
		this.iVariables["VarStr"] = new ServiceVariable("VarStr");
		this.iVariables["VarBin"] = new ServiceVariable("VarBin");
}


ServiceTestBasic.prototype.A_ARG_Increment_Value_Changed = function (aStateChangedFunction) {
    this.Variables().A_ARG_Increment_Value.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceTestBasic.prototype.A_ARG_Increment_Result_Changed = function (aStateChangedFunction) {
    this.Variables().A_ARG_Increment_Result.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceTestBasic.prototype.A_ARG_Decrement_Value_Changed = function (aStateChangedFunction) {
    this.Variables().A_ARG_Decrement_Value.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceTestBasic.prototype.A_ARG_Decrement_Result_Changed = function (aStateChangedFunction) {
    this.Variables().A_ARG_Decrement_Result.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceTestBasic.prototype.A_ARG_Toggle_Value_Changed = function (aStateChangedFunction) {
    this.Variables().A_ARG_Toggle_Value.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadBoolParameter(state)); 
	});
}
ServiceTestBasic.prototype.A_ARG_Toggle_Result_Changed = function (aStateChangedFunction) {
    this.Variables().A_ARG_Toggle_Result.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadBoolParameter(state)); 
	});
}
ServiceTestBasic.prototype.A_ARG_EchoString_Value_Changed = function (aStateChangedFunction) {
    this.Variables().A_ARG_EchoString_Value.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceTestBasic.prototype.A_ARG_EchoString_Result_Changed = function (aStateChangedFunction) {
    this.Variables().A_ARG_EchoString_Result.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceTestBasic.prototype.A_ARG_EchoBinary_Value_Changed = function (aStateChangedFunction) {
    this.Variables().A_ARG_EchoBinary_Value.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadBinaryParameter(state)); 
	});
}
ServiceTestBasic.prototype.A_ARG_EchoBinary_Result_Changed = function (aStateChangedFunction) {
    this.Variables().A_ARG_EchoBinary_Result.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadBinaryParameter(state)); 
	});
}
ServiceTestBasic.prototype.VarUint_Changed = function (aStateChangedFunction) {
    this.Variables().VarUint.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceTestBasic.prototype.VarInt_Changed = function (aStateChangedFunction) {
    this.Variables().VarInt.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadIntParameter(state)); 
	});
}
ServiceTestBasic.prototype.VarBool_Changed = function (aStateChangedFunction) {
    this.Variables().VarBool.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadBoolParameter(state)); 
	});
}
ServiceTestBasic.prototype.VarStr_Changed = function (aStateChangedFunction) {
    this.Variables().VarStr.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadStringParameter(state)); 
	});
}
ServiceTestBasic.prototype.VarBin_Changed = function (aStateChangedFunction) {
    this.Variables().VarBin.AddListener(function (state) 
	{ 
		aStateChangedFunction(SoapRequest.ReadBinaryParameter(state)); 
	});
}

ServiceTestBasic.prototype.ServiceName = function(){
	return this.iServiceName;
}

ServiceTestBasic.prototype.Variables = function(){
	return this.iVariables;
}

ServiceTestBasic.prototype.SubscriptionId = function () {
    return this.iSubscriptionId;
}

ServiceTestBasic.prototype.SetSubscriptionId = function (value) {
    this.iSubscriptionId = value;
}

ServiceTestBasic.prototype.Udn = function () {
    return this.iUdn;
}

ServiceTestBasic.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}

ServiceTestBasic.prototype.Subscribe = function () {
    SubscriptionManager.AddService(this);
}

ServiceTestBasic.prototype.Unsubscribe = function () {
    SubscriptionManager.RemoveService(this.SubscriptionId());
}


ServiceTestBasic.prototype.Increment = function(Value, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Increment", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("Value", Value);
    request.Send(function(result){
		result["Result"] = SoapRequest.ReadIntParameter(result["Result"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceTestBasic.prototype.Decrement = function(Value, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Decrement", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("Value", Value);
    request.Send(function(result){
		result["Result"] = SoapRequest.ReadIntParameter(result["Result"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceTestBasic.prototype.Toggle = function(Value, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Toggle", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteBoolParameter("Value", Value);
    request.Send(function(result){
		result["Result"] = SoapRequest.ReadBoolParameter(result["Result"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceTestBasic.prototype.EchoString = function(Value, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("EchoString", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("Value", Value);
    request.Send(function(result){
		result["Result"] = SoapRequest.ReadStringParameter(result["Result"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceTestBasic.prototype.EchoBinary = function(Value, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("EchoBinary", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteBinaryParameter("Value", Value);
    request.Send(function(result){
		result["Result"] = SoapRequest.ReadBinaryParameter(result["Result"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceTestBasic.prototype.SetUint = function(ValueUint, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetUint", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("ValueUint", ValueUint);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceTestBasic.prototype.GetUint = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetUint", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["ValueUint"] = SoapRequest.ReadIntParameter(result["ValueUint"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceTestBasic.prototype.SetInt = function(ValueInt, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetInt", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("ValueInt", ValueInt);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceTestBasic.prototype.GetInt = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetInt", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["ValueInt"] = SoapRequest.ReadIntParameter(result["ValueInt"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceTestBasic.prototype.SetBool = function(ValueBool, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetBool", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteBoolParameter("ValueBool", ValueBool);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceTestBasic.prototype.GetBool = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetBool", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["ValueBool"] = SoapRequest.ReadBoolParameter(result["ValueBool"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceTestBasic.prototype.SetMultiple = function(ValueUint, ValueInt, ValueBool, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetMultiple", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("ValueUint", ValueUint);
    request.WriteIntParameter("ValueInt", ValueInt);
    request.WriteBoolParameter("ValueBool", ValueBool);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceTestBasic.prototype.SetString = function(ValueStr, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetString", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("ValueStr", ValueStr);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceTestBasic.prototype.GetString = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetString", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["ValueStr"] = SoapRequest.ReadStringParameter(result["ValueStr"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceTestBasic.prototype.SetBinary = function(ValueBin, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetBinary", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteBinaryParameter("ValueBin", ValueBin);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceTestBasic.prototype.GetBinary = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("GetBinary", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["ValueBin"] = SoapRequest.ReadBinaryParameter(result["ValueBin"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}


ServiceTestBasic.prototype.ToggleBool = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("ToggleBool", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}



