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
* `HAS`
* `CYCLE`

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
                   ->    <ID>
                   ->    NULL
    
    <TARGET>       ->    <TARGET> <AND> <ID>
                   ->    <ID>
    
    <ACTION>       ->    <REPEAT>
                   ->    <CREATE>
                   ->    <REMOVE>
                   ->    <JOIN>
                   ->    <DISJOIN>
                   ->    <MERGE>
                   ->    <UNMERGE>
                   ->    <HAS>
    
    <RESOURCE>     ->    <GRAPH>
                   ->    <VERTEX>
                   ->    <CYCLE>

Example
-------

* `JOIN VERTEX @15 AND @20;`
* `REPEAT : 5 { CREATE VERTEX AT GRAPH @1 AND @7; }`
* `MERGE GRAPH @7 AND @38;`
* `REMOVE VERTEX @11 AND @12 AND @13 AND @14 AND @15;`
