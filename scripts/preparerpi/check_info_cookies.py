import re
import sys
import requests


normal_regex = re.compile('((?<=(something something))[0-9]{5})')
subtract_regex = re.compile('')


def get_url(breadcrumb):
    return 'https://{0}'.format(breadcrumb)


def get_breadcrumb(file_line, regexp):
    found_matches = regexp.findall(file_line)
    if found_matches is not None:
        return found_matches[0][0]

    raise ValueError(file_line)


def main(file_name, regexp):
    message_chars = []
    with open(file_name, 'r') as opened_file:
        for line in opened_file:
            breadcrumb = None
            try:
                breadcrumb = get_breadcrumb(line, regexp)
            except:
                pass

            if breadcrumb is not None:
                url_to_use = get_url(breadcrumb)
                result = requests.get(url_to_use)
                cookie_val = result.cookies['info']
                message_chars.append(cookie_val)
                print('{0}:{1}'.format(url_to_use, cookie_val))

    stringified_message = ''.join(message_chars)
    print(stringified_message)


if __name__ == '__main__':
    file_to_parse = sys.argv[1]
    main(file_to_parse)
