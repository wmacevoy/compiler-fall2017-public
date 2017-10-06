NUMBER -?(0|[1-9][0-9]*)(\.[0-9]+)?([eE][-+]?[0-9]+)?
STRING \"([\x00-\x21\x23-\x5b\x5d-\x7f]|[\0xc0-\0xdf].|[\xe0-\xef]..|[\xf0-\xf7]...|\\[\"\\/bfnrt]|\\u[0-9a-fA-F]{4,4})*\"



"[" { return OPEN_BRACE; }
"]" { return CLOSE_BRACE; }
