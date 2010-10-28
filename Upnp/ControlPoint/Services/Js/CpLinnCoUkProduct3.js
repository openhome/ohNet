 

/**
 * Proxy for linn.co.uk:Product:3
 */

var ServiceProduct = function(aId){	
	this.iUrl = window.location.protocol + "//" + window.location.host + "/" + aId + "/Product/control";
	this.iDomain = "linn.co.uk";
	if (this.iDomain == "upnp.org") {
		this.iDomain = "schemas.upnp.org";
    }
	this.iDomain = this.iDomain.replace(/\./,"-");
	this.iType = "Product";
	this.iVersion = "3";
	
	this.iVariables = {};
			this.iVariables["ProductType"] = new ServiceVariable("ProductType");
		this.iVariables["ProductModel"] = new ServiceVariable("ProductModel");
		this.iVariables["ProductName"] = new ServiceVariable("ProductName");
		this.iVariables["ProductRoom"] = new ServiceVariable("ProductRoom");
		this.iVariables["ProductStandby"] = new ServiceVariable("ProductStandby");
		this.iVariables["ProductSourceIndex"] = new ServiceVariable("ProductSourceIndex");
		this.iVariables["ProductSourceCount"] = new ServiceVariable("ProductSourceCount");
		this.iVariables["ProductSourceXml"] = new ServiceVariable("ProductSourceXml");
		this.iVariables["StartupSourceIndex"] = new ServiceVariable("StartupSourceIndex");
		this.iVariables["StartupSourceEnabled"] = new ServiceVariable("StartupSourceEnabled");
		this.iVariables["ProductSourceType"] = new ServiceVariable("ProductSourceType");
		this.iVariables["ProductSourceName"] = new ServiceVariable("ProductSourceName");
		this.iVariables["ProductSourceVisible"] = new ServiceVariable("ProductSourceVisible");
		this.iVariables["ProductAnySourceName"] = new ServiceVariable("ProductAnySourceName");
		this.iVariables["ProductAnySourceVisible"] = new ServiceVariable("ProductAnySourceVisible");
		this.iVariables["ProductAnySourceType"] = new ServiceVariable("ProductAnySourceType");
}


ServiceProduct.prototype.ServiceName = function(){
	return this.iType;
}

ServiceProduct.prototype.Variables = function(){
	return this.iVariables;
}

ServiceProduct.prototype.VariableNames = function(){
	var result = [];
	for (var variable in this.iVariables){
		if (this.iVariables.hasOwnProperty(variable)){
			result[result.length] = variable;
		}
	}
	return result;
}


ServiceProduct.prototype.Type = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Type", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aType"] = request.ReadStringParameter(result["aType"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.Model = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Model", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aModel"] = request.ReadStringParameter(result["aModel"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.Name = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Name", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aName"] = request.ReadStringParameter(result["aName"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.SetName = function(aName, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetName", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("aName", aName);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.Room = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Room", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aRoom"] = request.ReadStringParameter(result["aRoom"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.SetRoom = function(aRoom, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetRoom", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("aRoom", aRoom);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.Standby = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("Standby", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aStandby"] = request.ReadBoolParameter(result["aStandby"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.SetStandby = function(aStandby, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetStandby", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteBoolParameter("aStandby", aStandby);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.SourceCount = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SourceCount", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aSourceCount"] = request.ReadIntParameter(result["aSourceCount"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.SourceXml = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SourceXml", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aSourceXml"] = request.ReadStringParameter(result["aSourceXml"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.SourceIndex = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SourceIndex", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aSourceIndex"] = request.ReadIntParameter(result["aSourceIndex"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.SetSourceIndex = function(aSourceIndex, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetSourceIndex", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aSourceIndex", aSourceIndex);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.SetSourceIndexByName = function(aSourceName, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetSourceIndexByName", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("aSourceName", aSourceName);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.SetStartupSourceIndexByName = function(aSourceName, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetStartupSourceIndexByName", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteStringParameter("aSourceName", aSourceName);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.StartupSourceIndex = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("StartupSourceIndex", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aSourceIndex"] = request.ReadIntParameter(result["aSourceIndex"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.SetStartupSourceIndex = function(aSourceIndex, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetStartupSourceIndex", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aSourceIndex", aSourceIndex);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.StartupSourceEnabled = function(aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("StartupSourceEnabled", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.Send(function(result){
		result["aStartupSourceEnabled"] = request.ReadBoolParameter(result["aStartupSourceEnabled"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.SetStartupSourceEnabled = function(aStartupSourceEnabled, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetStartupSourceEnabled", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteBoolParameter("aStartupSourceEnabled", aStartupSourceEnabled);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.SourceSystemName = function(aSourceIndex, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SourceSystemName", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aSourceIndex", aSourceIndex);
    request.Send(function(result){
		result["aSourceName"] = request.ReadStringParameter(result["aSourceName"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.SourceName = function(aSourceIndex, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SourceName", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aSourceIndex", aSourceIndex);
    request.Send(function(result){
		result["aSourceName"] = request.ReadStringParameter(result["aSourceName"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.SetSourceName = function(aSourceIndex, aSourceName, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetSourceName", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aSourceIndex", aSourceIndex);
    request.WriteStringParameter("aSourceName", aSourceName);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.SourceType = function(aSourceIndex, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SourceType", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aSourceIndex", aSourceIndex);
    request.Send(function(result){
		result["aSourceType"] = request.ReadStringParameter(result["aSourceType"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.SourceVisible = function(aSourceIndex, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SourceVisible", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aSourceIndex", aSourceIndex);
    request.Send(function(result){
		result["aSourceVisible"] = request.ReadBoolParameter(result["aSourceVisible"]);	
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    

ServiceProduct.prototype.SetSourceVisible = function(aSourceIndex, aSourceVisible, aSuccessFunction, aErrorFunction){	
	var request = new SoapRequest("SetSourceVisible", this.iUrl, this.iDomain, this.iType, this.iVersion);		
    request.WriteIntParameter("aSourceIndex", aSourceIndex);
    request.WriteBoolParameter("aSourceVisible", aSourceVisible);
    request.Send(function(result){
	
		if (aSuccessFunction){
			aSuccessFunction(result);
		}
	}, function(message, transport) {
		if (aErrorFunction) {aErrorFunction(message, transport);}
	});
}
    


