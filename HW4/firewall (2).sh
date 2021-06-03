#!/bin/bash
#
#

ex=./firewall.exe
input=$(sed 's/$/n/g' <(cat))
s=0
while read line; do
    line=$(echo $line | cut -f1 -d"#" | tr -d ' ' | tr -d '\t')
    if [[ $line ]]; then
        rule=$(echo $line | cut -f1 -d",")
        n=1
        a=0
        packs=$input
        while [[ $rule && $packs && $packs != "" ]]; do
            a=1
            (( n++ ))
            x=$(sed 's/$/n/g' <(sed 's/n/\n/g' <(echo $packs) | $ex $rule))
            rule=$(echo $line | cut -f$n -d",")
            if [[ $x ]]; then
                packs=$x
            else
                packs=""
            fi
        done
        if [[ s -eq 0 ]]; then
            out=$packs
        else
            out="$out n $packs"
        fi
        s=1    
    fi
done < $1
grep -v '^$' <(cat <(sed 's/n/\n/g' <(echo $out)) | sort | uniq | tr -d ' \t')
