Command Grammar (Proposal)
===============

Overview
--------

The grammar defined here is used for parsing commands.
Commands can be obtained from user input, GUI front-ends, or third party applications.

Syntax
------

#### Token Types
There are four types of token: `ID`, `NUMBER`, `SYMBOL` and `KEYWORD`.

* `ID` represents any integer following the symbol '@' (e.g. @101).
* `NUMBER` represents any ordinary positive integer.
* `SYMBOL` represents `@`, `:`, `;`, `{`, or `}`.
* `KEYWORD` represents pre-defined tokens, which contain only alphabets.

#### Symbol

* `LBRACE     -  {`
* `RBRACE     -  }`
* `COLON      -  :`
* `SEMICOLON  -  ;`
* `@` has no token type as it is always part of `ID`.

#### Keyword

* `REPEAT`
* `CREATE`
* `REMOVE`
* `JOIN`
* `DISJOIN`
* `MERGE`
* `UNMERGE`
* `AT`
* `AND`

Grammar
-------
The grammar is of LR1 form as below.

    <QUERY>        ->    <CONDITION> <LBRACE> <OPERATION> <RBRACE>
                   ->    <STATEMENT>
    
    <CONDITION>    ->    <REPEAT> <COLON> <NUMBER>
    
    <OPERATION>    ->    <OPERATION> <STATEMENT>
    
    <STATEMENT>    ->    <ACTION> <RESOURCE> <MODIFIER> <SEMICOLON>
    
    <MODIFIER>     ->    <AT> <RESOURCE> <ID>
                   ->    <TARGET>
    
    <TARGET>       ->    <TARGET> <AND> <ID>
                   ->    <ID>
    
    <ACTION>       ->    <REPEAT>
                   ->    <CREATE>
                   ->    <REMOVE>
                   ->    <JOIN>
                   ->    <DISJOIN>
                   ->    <MERGE>
                   ->    <UNMERGE>
    
    <RESOURCE>     ->    <GRAPH>
                   ->    <VERTEX>

Example
-------

* `join vertex @15 and @20;`
* `repeat : 5 { create vertex at graph @1 and @7; }`
* `merge graph @7 and @38;`
* `remove vertex @11 and @12 and @13 and @14 and @15;`
