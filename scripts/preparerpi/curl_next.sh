#!/usr/bin/env bash

function create_url {
    echo "https://challenge.hiringsolved.com/breadcrumbs/${1}"
}

function string_contains {
    line_count=`echo ${1} | grep -Eo --regexp=${2} | wc -l`
    if [[ 0 -lt ${line_count} ]]; then
        return 0
    fi
    return 1
}

function get_next {
    breadcrumb_url=`create_url ${1}`
    get_breadcrumb=`curl -g ${breadcrumb_url}`
    echo ${get_breadcrumb} >> last_request_result2.txt

    breadcrumb_digits=`echo ${get_breadcrumb} | grep -Eo --regexp='([0-9]+)'`
    string_contains "${get_breadcrumb}" '([0-9]+)'
    has_digits=${?}
    breadcrumb_memo=0
    while [[ 0 -eq ${has_digits} ]]; do
        breadcrumb_memo=${breadcrumb_digits}
        breadcrumb_url=`create_url ${breadcrumb_digits}`

        get_breadcrumb=`curl -g ${breadcrumb_url}`
        echo ${get_breadcrumb} >> last_request_result2.txt

        breadcrumb_digits=`echo ${get_breadcrumb} | grep -Eo --regexp='([0-9]+)'`
        string_contains "${get_breadcrumb}" '([0-9]+)'
        has_digits=${?}

        string_contains "${get_breadcrumb}" 'going.$'

        operation_message=${?}
        if [[ 0 -eq ${operation_message} ]]; then
            string_contains "${get_breadcrumb}" 'Subtract'
            should_subtract=${?}
            if [[ 0 -eq ${should_subtract} ]]; then
                breadcrumb_digits=`expr ${breadcrumb_memo} - ${breadcrumb_digits}`
            else
                breadcrumb_digits=`expr ${breadcrumb_memo} + ${breadcrumb_digits}`
            fi
        fi

        string_contains "${get_breadcrumb}" 'suck'
        has_second_number=${?}

        if [[ 0 -eq ${has_second_number} ]]; then
            breadcrumb_digits=`echo ${get_breadcrumb} | grep -Eo --regexp='([0-9]+)$'`
        fi

        if [[ (54321 -eq ${breadcrumb_digits}) || (12345 -eq ${breadcrumb_digits}) ]]; then
            exit 0
        fi
    done;
}

get_next ${1}