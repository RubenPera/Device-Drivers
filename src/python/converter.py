import os
from typing import Dict, Tuple, List


class Line:
    state: int
    s_action: str
    i_action: int
    next_state: int

    def __init__(self, line: str):
        split_line = line.split(',')
        self.state = split_line[0]
        self.s_action = split_line[1]
        self.next_state = split_line[2]
        self.i_action = -1

    def __repr__(self):
        return '[{},{},{}]'.format(self.state, self.i_action, self.next_state)

    def action_replaces(self, actions):
        self.i_action = actions[self.s_action]
        return self


def interpret_ltsa_export():
    actions: Dict[str, int] = {}
    header: str = ''
    states: List[str] = []
    lines: List[Line]
    export_files: List[str] = [
        'CONTROLLER_EXPORT', 'STDIN_EXPORT', 'STDOUT_EXPORT']
    exports: List[Tuple[str, str]]

    header, states = cleaned_header_states('COMBINED')

    lines = [Line(line) for line in states]

    for line in lines:
        if line.s_action in actions:
            line.i_action = actions[line.s_action]
        else:
            line.i_action = len(actions)
            actions[line.s_action] = line.i_action

    print(actions)

    exports = [cleaned_header_states(file) for file in export_files]

    exports_as_lines = [export_to_line(export[1], actions) for export in exports]

    max_len = max([len(export) for export in exports_as_lines])

    for i in range(len(export_files)):
        print(export_files[i], exports_as_lines[i])
        print()

    lines_as_table(10, 10, exports_as_lines[0])

def lines_as_table(x_size, y_size, lines: List[Line]):
    for x in range(x_size):
        for y in range(y_size):
            print(get_value_to_print(x, y, lines), end='')
        print()


def get_value_to_print(x, y, lines: List[Line]):
    for line in lines:
        if line.state == x and line.i_action == y:
            return line.next_state

    return -1

def cleaned_header_states(name: str):
    export: str = read_export_from_file(name)
    export_cleaned: List[str] = cleenup_export(export)
    return get_header_states(export_cleaned)

def export_to_line(export: str, actions: Dict[str, int]):
    return [Line(line).action_replaces(actions) for line in export]


def action_replaced(line: Line, actions: Dict[str, int]):

    line.i_action = actions[line.s_action]


# def interpret_ltsa_export(name: str) -> Tuple[str, Dict[str, Dict[str, str]]]:
#     dictionary: Dict[str, Dict[str, str]] = {}
#     header: str = ''
#     states: List[str] = []

#     export: str = read_export_from_file(name)
#     export_cleaned: List[str] = cleenup_export(export)
#     header, states = get_header_states(export_cleaned)

#     return cleened_export_to_fsp_data(dictionary, header, states)


def get_header_states(export: List[str]) -> Tuple[str, List[str]]:
    return export[0], export[1:-1]


def cleenup_export(text: str) -> List[str]:
    text = text.replace('des', '')
    text = text.replace('(', '')
    text = text.replace(')', '')
    return text.split('\n')


def read_export_from_file(name: str) -> str:
    # file_dir = os.path.dirname(__file__)
    with open('{}.aut'.format(name), mode='r') as file:
        return file.read()


def cleened_export_to_fsp_data(dictionary: Dict[str, Dict[str, str]],
                               header: str,
                               states: List[str]) \
        -> Tuple[str, Dict[str, Dict[str, str]]]:
    begin_state: str = header.split(',')[0]

    for state in states:
        state_split: List[str] = state.split(',')
        if state_split[0] not in dictionary:
            dictionary[state_split[0]] = {}

        dictionary[state_split[0]][state_split[1]] = state_split[2]

    return begin_state, dictionary


def main():
    interpret_ltsa_export()


if __name__ == '__main__':
    main()
