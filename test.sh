RED='\033[0;31m'
GREEN='\033[32m'
NC='\033[0m'

function test() {
	input=$1
	# get expected output
	echo $input | bash 1> ./expected/output 2> ./expected/error

	# get actual output
	echo $input | ./minishell 1> ./actual/tmp 2> ./actual/error
	cat ./actual/tmp | grep -v '^minishell\$' > ./actual/output

	diff ./expected/output ./actual/output &> /dev/null
	result=$?
	if [ $result -eq 0 ]; then
		echo -e "${GREEN}OK${NC}: $input"
	else
		echo -e "${RED}KO${NC}: $input"
		diff ./expected/output ./actual/output > ./diff/diff
	fi
}

function test_dx() {
	input=$1
	input_dx=$1' || echo $? && echo $?'
	# get expected output
	echo $input_dx | bash 1> ./expected/output 2> ./expected/error

	# get actual output
	echo $input_dx | ./minishell 1> ./actual/tmp 2> ./actual/error
	cat ./actual/tmp | grep -v '^minishell\$' > ./actual/output

	diff ./expected/output ./actual/output &> /dev/null
	result=$?
	if [ $result -eq 0 ]; then
		echo -e "${GREEN}OK${NC}: $input"
	else
		echo -e "${RED}KO${NC}: $input"
		diff ./expected/output ./actual/output > ./diff/diff
	fi
}

mkdir expected
mkdir actual
mkdir diff

# test case
echo '<------------ starting testcase ------------>'

# builtin echo
echo ''
echo '[echo testcase]'
test_dx 'echo'
test_dx 'echo hello'
test_dx 'echo -n hello'

# builtin pwd
echo ''
echo '[pwd testcase]'
test_dx 'pwd'

# basic testcase
echo ''
echo '[basic testcase]'
test_dx 'ls'
test_dx 'echo'
test_dx '/bin/ls'
test_dx '/bin/ls -a'
test_dx 'lsc'
test ' '
test_dx 'echo hello'
test_dx 'echo hello world'
test_dx 'cat main.c'
test_dx 'echo -n hello'
test_dx 'echo "hello"'

# pipe case
echo ''
echo '[pipe testcase]'
test 'ls | cat'
test 'ls | cat | ls'
test 'ls | cat | ls | cat'
test 'cat | cat | ls'
test 'ls | ls | cat'
test 'cat | ls | cat'
test 'echo "'\$PATH'"'
test "echo '\"\$PATH\"'"

echo ''
echo '<------------ finished testcase ------------>'

rm -rf expected
rm -rf actual
rm -rf diff