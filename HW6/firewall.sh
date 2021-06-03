#!/bin/bash


input=`cat`

output=""

	while read rule
	do
		rule=`echo "$rule" | sed '/^$/d' | sed 's/ //g' | grep -o '^[^#]*'`
		if [[ -n $rule ]]; then
			readarray -d , -t filter <<< "$rule"
			
			feasible_rule=`echo "$input" | ./firewall.exe "${filter[0]}" | ./firewall.exe "${filter[1]}" | ./firewall.exe "${filter[2]}" | ./firewall.exe "${filter[3]}"`
			output+=`echo "${feasbile_rule}" | sed '/^$/d' | sort -u `
			output+="\n"
		fi
	done < "$1"
	
	echo -e "${output}" | sed 's/ //g' | sed '/^$/d' | sort -u
		
