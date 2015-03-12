function CallbackFailure()
{
    alert("CallbackFailure");
}

function UpdateCallbackResponse(aStringSent, aStringReceived)
{
    alert("UpdateCallbackResponse sent: "+aStringSent+", rcvd: "+aStringReceived);
}

function UpdateCallbackError(aStringSent)
{
    alert("UpdateCallbackError: "+aStringSent);
}

function LongPollCallbackResponse(aResponse)
{
    alert("LongPollCallbackResponse: "+aResponse);
}



function DummyCallbackFailure()
{
    //alert("DummyCallbackFailure");
    // FIXME - if this happens, replace the body until the connection can be re-established
    // at which point, just reload the whole page?
    // (That would cause long-polling to be restarted again after the connection has just been
    // re-established.)
    var content = "<h1>Error: HTTP Framework cannot connect to server</h1>";
    document.body.innerHTML = content;
}

function DummyUpdateCallbackResponse(aStringSent, aStringReceived)
{
    //alert("DummyUpdateCallbackResponse sent: "+aStringSent+", rcvd: "+aStringReceived);
}

function DummyUpdateCallbackError(aStringSent)
{
    //alert("DummyUpdateCallbackError: "+aStringSent);
}

/**
 * Test long polling functionality of the HttpFramework.
 *
 * This function:
 * - starts long polling
 * - sends the numbers 1..10,000 to the server
 * - receives long-polling response from server application, which will be an
 *   echo of the message sent in
 * - updates a text area of the web page with the response
 * - displays the total time taken for all send/receive pairs
 * - displays the rate of send/receives per minute
 */

function PerformLongPollTest(aTotal, aInterval)
{
    var count = 1;
    var startTime = 0;

    var LongPollStarted = function()
    {
        startTime = performance.now();
        WebUi.SendUpdateToServer(count+'\r\n', DummyUpdateCallbackResponse, DummyUpdateCallbackError);
        count++;
    }

    var RoundToTwoDecimalPlaces = function(aValue)
    {
        return Math.round(aValue*100)/100;
    }

    var UpdateFinal = function()
    {
        var endTime = performance.now();
        var durationMs = RoundToTwoDecimalPlaces(endTime-startTime);
        var durationSecs = RoundToTwoDecimalPlaces(durationMs/1000);
        var rateMs = count/durationMs;
        var rateMsRounded = RoundToTwoDecimalPlaces(rateMs);
        var timePerUpdateMs = RoundToTwoDecimalPlaces(durationMs/count);
        document.getElementById("echoduration").innerHTML = durationMs+" ms ("+durationSecs+" s)";
        document.getElementById("echorate").innerHTML = rateMsRounded+" updates/ms";
        document.getElementById("echosingle").innerHTML = timePerUpdateMs+" ms";

        // Terminate long polling.
        WebUi.EndLongPolling();
    }

    /**
     * When this function receives a response, it initiates the next echo.
     */
    var LongPollCountResponse = function(aResponse)
    {
        if (aResponse % aInterval == 0) {
            var elem = document.getElementById("echoresponse");
            var content = elem.innerHTML;
            content = content+"<br>"+aResponse; // FIXME - aResponse will probably have "\r\n" following it - almost certainly don't want this
            elem.innerHTML = content;
        }

        // Initiate next echo.
        if (count <= aTotal) {
            // FIXME - what if long polling connection is dropped/lost in the middle of sending these updates - there will be no appropriate session ID.
            WebUi.SendUpdateToServer(count+'\r\n', DummyUpdateCallbackResponse, DummyUpdateCallbackError);
            count++;
        }
        else {
            UpdateFinal();
        }
    }

    WebUi.StartLongPolling(LongPollStarted, LongPollCountResponse, DummyCallbackFailure);
}

function SubmitLongPollForm()
{
    var form = document.forms["formLongPollTest"];
    var count = form["echocount"].value;
    var interval = form["echointerval"].value;
    PerformLongPollTest(count, interval);
}

function StartLongPolling()
{
    var LongPollStarted = function()
    {
        // Do nothing.
    }

    var UpdateCallback = function(aResponse)
    {
        // Do nothing.
    }

    WebUi.StartLongPolling(LongPollStarted, UpdateCallback, DummyCallbackFailure);
}

function EndLongPolling()
{
    WebUi.EndLongPolling();
}
