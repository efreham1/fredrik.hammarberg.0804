# Initial Profiling Results

FORMAT:
funktionsnamn (anrop,
Topp 3 funktioner för varje input:
----------------------------------------------------------------
1k:
  %   cumulative   self              self     total           
 time   seconds   seconds    calls  Ts/call  Ts/call  name    
  0.00      0.00     0.00    52075     0.00     0.00  get_sentinel_bucket
  0.00      0.00     0.00    13959     0.00     0.00  string_eq
  0.00      0.00     0.00     2231     0.00     0.00  string_lt
----------------------------------------------------------------
10k:
  %   cumulative   self              self     total           
 time   seconds   seconds    calls  Ts/call  Ts/call  name    
  0.00      0.00     0.00   934203     0.00     0.00  string_eq
  0.00      0.00     0.00   476590     0.00     0.00  get_sentinel_bucket
  0.00      0.00     0.00    40785     0.00     0.00  string_lt
----------------------------------------------------------------
16k:
  %   cumulative   self              self     total           
 time   seconds   seconds    calls  ms/call  ms/call  name    
 47.14      0.08     0.08    16992     0.00     0.01  ioopm_hash_table_has_key
 29.46      0.13     0.05                             get_entry
 17.68      0.16     0.03 24027334     0.00     0.00  string_eq
----------------------------------------------------------------


* Alla funktionerna är definierade i den egna koden.

* Är de topp 3 funktionerna samma för varje input?
Nej! För 1k och 10k ord finns samma funktioner i topp 3:
     * get_sentinel_bucket
     * string_eq
     * string_lt
men antalet anrop varierar mellan dem.
För 16k ord finns string_eq fortfarande kvar i toppen men ht_has_key och get_entry dominerar tidsmässigt.

*Märkbara trender:
Antalet anrop till string_eq ökar kraftigt när antalet ord ökar.
Att köra funktionen ht_has_key tar också lång tid.
string_lt tar först längre tid men minskar när det blir fler ord.

*Förklaring:
string_eq och string_lt är kopplade till ht_has_key respektive ht_insert.
När det rör sig om få ord finns det sannolikt mindre key/value-pairs vilket gör att det som tar längst tid är att sätta in värdena för första gången. Sedan funkar freq-programmet så att den kollar efter redan existerande keys och inkrementerar dess int-värde om strängen matchar key. Dvs, man anropar has_key. Desto fler entries i en bucket, desto fler entries blir det att gå igenom. Om man har en textfil med mer ord följer det därför logiskt att ht_has_key och därmed string_eq (eftersom keys är strings i detta fall) anropas mer och tar längre tid än att sätta in entries.

Ett sätt att potentiellt göra programmet snabbare är att ha flera buckets samt en hashfunktion som gör att föredlningen av entries mellan buckets är jämn.




