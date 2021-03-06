#!/bin/bash
#script argumets:
#total_players: total players count
#search_result: how many times 'Midfielder' has appeared within players' page
#script name: scrape_players
#these comments are divided linewise, keeping given commands commentless
#(lines: 2,3) create a utility text file, which will hold all players' links
#(line: 4) how many links there are and save this count as'total_players'
#(line: 5) initiate a output file, its first line stating total players count
#(line: 6) loop declaration, iterating for each link wihtin utility text file
#(line: 8) wget creates 'overview' file, see complementary comment (line 13)
#(line: 9) searching in 'overview' how many times 'Midfielder' appeared
#(line: 10) omitting players which did not match 'Midfielder' requirement
#(line: 11) concatenates given string and search result for each matching link
#(line: 13) deleting 'overview' file to ensure next iteration of line 11
#(line: 13) continue: will result in an iterated 'overview' file

wget https://www.premierleague.com/players
grep -oP "(/players/)[0-9]+/[a-zA-Z-]+(/overview)" players > urls.txt
sed -i 's/\/players/https:\/\/www\.premierleague\.com\/players/' urls.txt
total_players=`cat urls.txt | wc -l`
echo "Total_players: $total_players" > Results.csv
for link in `cat urls.txt`
do
	wget $link
	search_result=`cat overview | grep -oP "Midfielder|midfielder+" | wc -l`
	if [[ $search_result -gt 0 ]] ; then
		echo "$link, Midfielder, $search_result" >> Results.csv
	fi
	rm overview
done
rm players
rm urls.txt
