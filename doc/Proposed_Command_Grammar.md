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

    <QUERY>     -> <CONDITION> <LBRACE> <OPERATION> <RBRACE>
    
    <CONDITION> -> <REPEAT> <COLON> <NUMBER>
    
    <OPERATION> -> <OPERATION> <STATEMENT>
    
    <STATEMENT> -> <ACTION> <RESOURCE> <MODIFIER> <SEMICOLON>
    
    <MODIFIER>  -> <AT> <RESOURCE> <ID>
                -> <TARGET>
    
    <TARGET>    -> <TARGET> <AND> <ID>
                -> <ID>
