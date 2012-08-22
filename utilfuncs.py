def set_env_verbose(conf, varname, value):
    conf.msg(
        'Setting %s to' % varname,
        'True' if value is True else
        'False' if value is False else
        value)
    setattr(conf.env, varname, value)
    return value
