import re
import os


def find_single_line_patterns(text_lines, regex_obj):
    single_line_patterns = []
    for line_number in range(0, len(text_lines) - 1):
        single_line_patterns.append([(line_number, 'Line')])
        line_matches = regex_obj.findall(text_lines[line_number])
        if len(line_matches) > 0:
            single_line_patterns[line_number].extend(line_matches)
    return single_line_patterns


def find_column_patterns(columns, regex_obj):
    column_patterns = []
    for column_number in range(0, len(columns) - 1):
        column_patterns.append([(column_number, 'Column')])
        column_matches = regex_obj.findall(columns[column_number])
        if len(column_matches) > 0:
            column_patterns[column_number].extend(column_matches)
    return column_patterns


def slice_lines_into_columns(text_lines):
    text_columns = ['' for _ in range(len(text_lines[0]))]

    for line_number in range(0, len(text_lines)-1):
        line_text = text_lines[line_number]
        for column_number in range(0, len(line_text)-1):
            column_text = text_columns[column_number] + line_text[column_number]
            text_columns[column_number] = column_text

    return text_columns


def find_patterns(text_lines, regex_obj):
    line_patterns = find_single_line_patterns(text_lines, regex_obj)

    text_columns = slice_lines_into_columns(text_lines)
    column_patterns = find_column_patterns(text_columns, regex_obj)

    return line_patterns, column_patterns,


def print_pattern_matches(pattern_type, pattern_array):

    print('=========================')
    print('{0}'.format(pattern_type))
    print('=========================')

    for entry in pattern_array:
        entry_text = ['{0}{1}'.format(match_tuple[1], match_tuple[0]) for match_tuple in entry]
        print(', '.join(entry_text))


if __name__ == '__main__':
    text_file = []

    while True:
        try:
            line_in = input('Enter line\n')
        except EOFError:
            break
        else:
            text_file.append(line_in)

    regex = re.compile('((?<=([a-z]{4}))[A-Z]{4})')

    patterns = find_patterns(text_file, regex)
    print_pattern_matches('LINE PATTERNS', patterns[0])
    print_pattern_matches('COLUMN PATTERNS', patterns[1])
