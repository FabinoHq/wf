    _______                               ______________________
    \\ .   \                     ________/ . . . . . . . . . . /
     \\ .   \     ____       ___/   . . .     ________________/
      \\ .   \   //   \   __/  . .  _________/ .  .  .  .  /
       \\ .   \_//     \_//     ___/    //      __________/
        \\ .   \/   _   \/    _/       // .    /___
         \\ .      /\\       /        // .    ____/
          \\ .    /  \\     /       _// .   /
           \\ .  /    \\   /     _//  .    /
            \\__/      \\_/    //_________/


	`include.wf` : Include a program file

	;Comment; : Write a comment between ; and ;

	123 : Store integer 123 into the register
	0x007B : Store integer 123 into the register
	0b01111011 : Store integer 123 into the register
	'c' : Store ASCII value of character 'c' into the register
	"string" : Store string "string" in memory at current pointed address

	:label: : Define new label
	@label@ : Jump unconditionally to label
	=label= : Jump to label if register value is equal to zero (r == 0)
	!label! : Jump to label if register value is not equal to zero (r != 0)
	>label> : Jump to label if register value is greater than zero (r > 0)
	<label< : Jump to label if register value is less than zero (r < 0)

	$label$ : Function call (Jump unconditionally to label)
	^ : Function return (Jump unconditionally to caller)

	\ : Swap current pointer address and back pointer address (p <=> q)
	} : Increment current pointer address (p = p+1)
	{ : Decrement current pointer address (p = p-1)
	] : Set the current pointer address from the register (p = r)
	[ : Load the current pointer address into the register (r = p)
	~ : Swap the register and the back register (r <=> b)
	# : Load current pointed value into the register (r = *p)
	_ : Store current register value at current pointed address (*p = r)

	+ : Add register value and back register value (r = r + b)
	- : Subtract register value and back register value (r = r - b)
	* : Multiply register value and back register value (r = r * b)
	/ : Divide register value by back register value (r = r / b)
	% : Modulo of register value and back register value (r = r % b)

	& : Bitwise AND between register value and back register value (r = r & b)
	| : Bitwise OR between register value and back register value (r = r | b)

	, : read one input byte into the register
	. : output one byte from the register
	) : Set current I/O cursor position from the register and back register
	( : Load current I/O cursor position into the register
	? : Set I/O mode based on the value in the register (terminal or file)
