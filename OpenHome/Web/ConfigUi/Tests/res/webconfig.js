function StartLongPolling()
{
    var LongPollStarted = function()
    {
        // Do nothing.
    }

    var CreateNumElement = function(aJsonConfigNumVal)
    {
        var elemInput = document.createElement("input");
        elemInput.type = "text";
        elemInput.id = aJsonConfigNumVal.key;
        elemInput.name = aJsonConfigNumVal.key;
        elemInput.onblur = function () {SendUpdate(elemInput.id, elemInput.value);} // FIXME - pass through an input validation function (check it's a num, then check limits)
        return elemInput;
    }

    var CreateChoiceElement = function(aJsonConfigChoiceVal)
    {
        var options = aJsonConfigChoiceVal.meta.options;
        var elemSelect = document.createElement("select");
        elemSelect.id = aJsonConfigChoiceVal.key;
        elemSelect.name = aJsonConfigChoiceVal.key;
        elemSelect.multiple = false;
        for (var i=0; i<options.length; i++) {
            var option = document.createElement("option");
            option.text = options[i];
            elemSelect.add(option);
        }
        elemSelect.onblur = function () {SendUpdate(elemSelect.id, elemSelect.value);}
        return elemSelect;
    }

    var CreateTextElement = function(aJsonConfigTextVal)
    {
        var elemInput = document.createElement("input");
        elemInput.type = "text";
        elemInput.id = aJsonConfigTextVal.key;
        elemInput.name = aJsonConfigTextVal.key;
        elemInput.onblur = "SendUpdate(id, value)"; // FIXME - take this as parameter?
        elemInput.onblur = function () {SendUpdate(elemInput.id, elemInput.value);}
        return elemInput;
    }

    var CreateValElement = function(aJsonConfigVal)
    {
        if (aJsonConfigVal.type == "numeric") {
            return CreateNumElement(aJsonConfigVal)
        }
        else if (aJsonConfigVal.type == "choice") {
            return CreateChoiceElement(aJsonConfigVal)
        }
        else if (aJsonConfigVal.type == "text") {
            return CreateTextElement(aJsonConfigVal)
        }
        else {
            // Bad ConfigVal type.
        }
    }

    var CreateElement= function(aJsonConfigVal)
    {
        var elem = document.getElementById(aJsonConfigVal.key);
        if (elem != null) {
            return elem;
        }

        var containerId = "ConfigValContainer"
        var container = document.getElementById(containerId);
        if (container == null) {
            alert("Error: Config.StartLongPolling.CreateElement() No element with id \""+containerId+"\"");
            return null;
        }
        else {
            var key = aJsonConfigVal.key;

            // Create a name column.
            var colName = document.createElement("td");
            var nameText = document.createTextNode(key);
            colName.appendChild(nameText);

            // Create an input column.
            var colInput = document.createElement("td");
            var elemVal = CreateValElement(aJsonConfigVal); // value is not set; set outwith this function
            colInput.appendChild(elemVal);

            // Create a row to hold the columns of data.
            var row = document.createElement("row");
            row.appendChild(colName);
            row.appendChild(colInput);

            container.appendChild(row);

            // return row;
            return document.getElementById(key);
        }
    }

    // FIXME - move this to config.js
    var UpdateCallback = function(aResponse)
    {
        if (aResponse != null && aResponse != "") {
            var key = aResponse.key;
            var val = aResponse.value;
            var elem = document.getElementById(key);
            if (elem != null) {
                elem.value = val;       // FIXME - is this valid for all element types in use?
            }
            else {
                // Element not found; may be one that has just been discovered.
                // Check if an element can be created and set the value. Ignore it
                // otherwise.
                elem = CreateElement(aResponse);
                if (elem != null) {
                    elem.value = val;   // FIXME - is this valid for all element types in use?
                }
            }
        }
    }

    // FIXME - move this to WebUi? - maybe not
    function DummyCallbackFailure()
    {
        // This, combined with the reconnect behaviour, causes long-polling to
        // be restarted again after the connection has just been re-established.
        var content = "<h1>Error: HTTP Framework cannot connect to server</h1>";
        document.body.innerHTML = content;
    }

    Config.StartLongPolling(LongPollStarted, UpdateCallback, DummyCallbackFailure);
}

function EndLongPolling()
{
    Config.EndLongPolling();
}

function SendUpdate(aKey, aValue)
{

    var DummyUpdateCallbackResponse = function(aStringSent, aStringReceived)
    {
        //alert("DummyUpdateCallbackResponse sent: "+aStringSent+", rcvd: "+aStringReceived);
    }

    var DummyUpdateCallbackError = function(aStringSent)
    {
        //alert("DummyUpdateCallbackError: "+aStringSent);
    }

    Config.SendUpdateToServer(aKey, aValue, DummyUpdateCallbackResponse, DummyUpdateCallbackError);
}