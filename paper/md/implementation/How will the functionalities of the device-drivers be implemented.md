# Research

## What can the functionality of the device-drivers be implemented

In this section the implemented of the two device-drivers will be given. In the FSP model the name stdin_driver was used for device-driver0 and stdout_driver for device-driver1, these names will also be used in this paper.

When executing an action the device-drivers execute the specified action and determine their new sensitivity-list.

### How is the functionality of device-driver0 implemented

As specified in the Requirements the functionality of stdin_driver will be to read from stdin. The following code snippet is used:

``` C
void execute_action(
    finite_state_machine_t *self,
    int action,
    int sensitivity_list[ACTIONS])
{

    set_sensitivity_list_empty(sensitivity_list);

    switch (action)
    {
    case CHECK_STDIN_VALUE:
        action_check_stdin_value(sensitivity_list);
        break;

    default:
        break;
    }
}

void action_check_stdin_value(int sensitivity_list[ACTIONS])
{
    int key = KEY_S;
    int input = 0;
    int i = 0;

    input = getchar();

    for (i = 0; i < KEYS; i++)
    {
        if (input == ALLOWED_KEYS[i])
        {
            key = KEY_ACTIONS[i];
        }
    }

    sensitivity_list[key] = HAS_ACTION;
}
```

### How can the functionality of device-driver1 be implemented

As specified in the Requirements the functionality of device-driver1 will be to write to stdout. The following code snippet is used:

``` C

```

| Name | Explanation | Input arguments | Return value |
|------|-------------|-----------------|--------------|
| putchar | puts the passed character on the screen and returns the same character | Character to write | Written character |
| puts | Writes the provided string and a trailing newline to stdout | String to write | Status |
| printf | writes the output to the stdout and produces the output according to the format provided | Format, List of Format variables to write | Status |

The above commands can be used to write to the stdout and can be used to implemented the second device-driver its behavior.