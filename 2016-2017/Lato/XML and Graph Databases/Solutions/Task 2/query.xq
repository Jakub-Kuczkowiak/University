(: Bartosz Jan Bednarczyk :)

(: Zad 1
fn:doc("r_and_j.xml")/PLAY/(ACT|ACT/SCENE)/TITLE
 :)

(: Zad 2
fn:doc("r_and_j.xml")/distinct-values(PLAY/ACT[3]/SCENE[ (position() = 1) or (position() = 3) ]//SPEAKER)
 :)

(: Zad 3
fn:doc("r_and_j.xml")/distinct-values((PLAY/ACT/SCENE)[ (position() = 2) or (position() = 8) ]//SPEAKER)
 :)

(: Zad 4
(fn:doc("r_and_j.xml")/PLAY/ACT/SCENE)[./SPEECH/SPEAKER = 'JULIET']/TITLE
 :)

(: Zad 5 - Wersja bez let'a
fn:doc("r_and_j.xml")/PLAY/ACT[1]/SCENE[count(.//LINE) = fn:max(fn:doc("r_and_j.xml")/PLAY/ACT[1]/SCENE/fn:count(.//LINE))]/TITLE
:)

(: Zad 5 - wersja z let'em
let $scenes := fn:doc("r_and_j.xml")/PLAY/ACT[1]/SCENE
let $max := fn:max($scenes/fn:count(.//LINE))
return $scenes[fn:count(.//LINE) = $max]/TITLE
 :)

(: Zad 6 
let $scenes := fn:doc("r_and_j.xml")/PLAY/ACT[2]/SCENE
let $min := fn:min($scenes/fn:count(.//SPEAKER))
return $scenes[fn:count(.//SPEAKER) = $min]/TITLE
 :)

(: Zad 7
let $scenes := fn:doc("r_and_j.xml")/PLAY/ACT/SCENE[./SPEECH/SPEAKER = 'ROMEO']
let $lines := $scenes//LINE/text()
let $text := string-join($lines, ' ')
let $replaced := replace($text, '[^a-zA-Z0-9]', ' ')
let $tokenized := tokenize($replaced, "\s+")
return count($tokenized[.="love"])
 :)

(: Zad 8
let $persons := distinct-values(fn:doc("r_and_j.xml")//SPEAKER)
for $name in $persons
	let $speeches := fn:doc("r_and_j.xml")//SPEECH[./SPEAKER = $name]
	let $lines := $speeches//LINE/text()
	let $text := string-join($lines, ' ')
	let $replaced := replace($text, '[^a-zA-Z0-9]', ' ')
	let $tokenized := tokenize($replaced, "\s+")
	return
		if (count($tokenized[.="no"]) = 0)
		then $name else ""
 :)

(: Zad 9 
let $scenes := fn:doc("r_and_j.xml")/PLAY/ACT/SCENE[ (.//SPEAKER = "ROMEO") and (.//SPEAKER = "JULIET") and not(.//SPEAKER = "BENVOLIO") ]
let $speakers := distinct-values($scenes//SPEAKER[.!="ROMEO" and .!="JULIET"])
return ($speakers[1], $speakers[2], $speakers[3])  
 :) 

(: Zad 10
let $speakers := distinct-values(fn:doc("r_and_j.xml")/PLAY/ACT[last()]//SPEAKER)
return ($speakers[1], $speakers[2], $speakers[3])
 :)

(: Zad 11
((fn:doc("r_and_j.xml")//SPEECH[./SPEAKER = "JULIET"])//LINE)[1] | ((fn:doc("r_and_j.xml")//SPEECH[./SPEAKER = "ROMEO"])//LINE)[last()]
 :)

(: Zad 12
let $scenes := fn:doc("r_and_j.xml")/PLAY/ACT/SCENE[(.//SPEAKER = "JULIET")]
return $scenes//SPEECH[last()]/LINE[last()]
 :)

(: Zad 13
let $scenes := fn:doc("r_and_j.xml")/PLAY/ACT/SCENE[(.//SPEAKER = "ROMEO")]
return $scenes//SPEECH[1]/LINE[1]
 :)

