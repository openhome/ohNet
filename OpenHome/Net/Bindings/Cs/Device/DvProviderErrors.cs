using System;

namespace OpenHome.Net.Device
{
    /// <summary>
    /// Thrown when an action with no registered delegate is invoked.  Will not be visible to external code
    /// </summary>
    public class ActionDisabledError : Exception
    {
    }

    /// <summary>
    /// Thrown when an invoked action fails.  Will not be visible to external code
    /// </summary>
    public class ActionError : Exception
    {
        public uint Code { get; private set; }
        public string Msg { get; private set; }

        public ActionError()
        {
        }
        public ActionError(string aMessage)
            : base(aMessage)
        {
            Msg = aMessage;
        }
        public ActionError(uint aCode, string aMessage)
            : base(String.Format("{0}: {1}", new object[] { aCode, aMessage }))
        {
            Code = aCode;
            Msg = aMessage;
        }
    }

    /// <summary>
    /// Thrown when an attempt is made to update a property to a value not in the AllowedValues range/set
    /// </summary>
    public class PropertyUpdateError : Exception
    {
    }

    /// <summary>
    /// Thrown when an attempt is made to get/set a property that has not been enabled.
    /// </summary>
    public class PropertyDisabledError : Exception
    {
    }
}
