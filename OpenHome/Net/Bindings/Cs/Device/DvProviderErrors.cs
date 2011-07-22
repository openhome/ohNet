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
    }

    /// <summary>
    /// Thrown when an attempt is made to update a property to a value not in the AllowedValues range/set
    /// </summary>
    public class PropertyUpdateError : Exception
    {
    }
}
