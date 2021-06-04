#!/bin/bash

#save input
pack_in=`cat`

output=""

	while read rule
	do
		#deals with spaces,line and comments
		rule=`echo "$rule" |sed 's/ //g' | sed '/^$/d' | grep -o '^[^#]*'`
		
		if [[ -n $rule ]]; then
			#turn the rule into filters
			readarray -d , -t filters <<< "$rule"
			#check packets
			
			#uses the filters ont the packets
			packs_out_rules_new=`echo "$pack_in" | ./firewall.exe "${filters[0]}" | ./firewall.exe "${filters[1]}" | ./firewall.exe "${filters[2]}" | ./firewall.exe "${filters[3]}"`
			#create output
			#add the passed packets to output
			output+=`echo "${packs_out_rules_new}" | sed '/^$/d' | sort -u `
			output+="\n"
		fi
		
	 done < "$1" # $1 is the argument of rules filename 

	echo -e "${output}" | sed '/^$/d' | sed 's/ //g' | sort -u



