<?php

function quizsolved()
{
  global $pguser;
  if (isset($pguser))
      record_quiz_attempt($pguser,"p_greek_4","pass");
}

$browser_title                = _("Greek Transliteration Quiz");
$intro_title                  = _("Greek Transliteration Quiz, page 4");
$initial_instructions         = $initial_instructions__greek;
$ocr_text                     = "how they kicked their crowns away from\nthem. Of all the enemies they had, they\nthemselves were the most fatal:\n\n[Greek: \"&Ocirc; popoi, ohion d&ecirc; nu theous\nBroto&igrave; aitio&ocirc;ntai,\nex &ecirc;me&ocirc;n gap phaoi kak\nemmenai oi de kai antoi\noph&ecirc;ioin ataothali&ecirc;oin nter\nmoron alge eChouin]";
$solutions                    = array("how they kicked their crowns away from\nthem. Of all the enemies they had, they\nthemselves were the most fatal:\n\n[Greek: Ô popoi, hoion dê ny theous\nbrotoi aitioôntai,\nex hêmeôn gar phasi kak'\nemmenai; hoi de kai autoi\nsphêsin atasthaliêsin hyper\nmoron alge' echousin.]");
$solved_message               = "<h2>" . _("Quiz successfully solved") . "</h2>\n" .
                                    "<p>" . _("Congratulations, no errors found!") . "</p>\n" .
                                    "<h3>" . _("Handy Tip") . "</h3>\n" .
                                    "<p>" . _("Occasionally a Project Manager asks proofreaders to include accents in their Greek transliterations.  Since this is not part of the normal guidelines, please only do this if the PM or PPer requests it.  If there are no special instructions, then you should ignore all Greek accents except the rough breathing mark.") . "</p>";


// error messages

$messages["beta_eszett"] = array(
    "message_text" => "<h2>" . _("Beta proofread as &szlig;") . "</h2>\n" .
        "<p>" . _("The &szlig; character is not a Greek letter.  Please transliterate &beta; (beta) as '<tt>b</tt>', as shown in the Greek transliteration tool.") . "</p>",
    "hints" => array(),
);
$messages["Brotoi"] = array(
    "message_text" => "<h2>" . _("Scanno") . "</h2>\n" .
        "<p>" . _("There is still a scanno: a capital '<tt>B</tt>' in the text where there is the Greek letter &beta; (beta, transliterated '<tt>b</tt>') in the image.") . "</p>",
    "hints" => array(),
);
$messages["p_t"] = array(
    "message_text" => "<h2>" . _("Scanno") . "</h2>\n" .
        "<p>" . _("There is still a scanno: a '<tt>t</tt>' in the text where there is the Greek letter &pi; (pi, transliterated '<tt>p</tt>') in the image.") . "</p>",
    "hints" => array(),
);
$messages["missings"] = array(
    "message_text" => "<h2>" . _("Missing letter") . "</h2>\n" .
        "<p>" . _("There is an '<tt>s</tt>' (the transliteration of &sigma;, sigma) missing in your transliteration.") . "</p>",
    "hints" => array(),
);
$messages["missingperiod"] = array(
    "message_text" => "<h2>" . _("Scanno") . "</h2>\n" .
        "<p>" . _("There is still a scanno in the text: a period (<tt>.</tt>) was omitted by the OCR software.") . "</p>",
    "hints" => array(),
);


// error checks

$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("\n "), "case_sensitive" => TRUE, "error" => "P_indent");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("<i>", "</i>"), "case_sensitive" => FALSE, "error" => "P_italmarkup");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("/*", "*/"), "case_sensitive" => TRUE, "error" => "P_poemmarkup");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("&#964;", "&#945;", "&#954;", "&#959;"), "case_sensitive" => TRUE, "error" => "G_unicode");
$tests[] = array("type" => "expectedtext", "searchtext" =>  array("brotoi", "gar", "phasi", "autoi", "echousin"), "case_sensitive" => TRUE, "error" => "G_nochange");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("greek"), "case_sensitive" => TRUE, "error" => "G_lcgreek");
$tests[] = array("type" => "expectedtext", "searchtext" =>  array("[Greek:"), "case_sensitive" => TRUE, "error" => "G_nomarkup");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("[Greek:\n"), "case_sensitive" => TRUE, "error" => "G_markupline");
$tests[] = array("type" => "expectedtext", "searchtext" =>  array("[Greek: "), "case_sensitive" => TRUE, "error" => "G_markupspace");
$tests[] = array("type" => "expectedtext", "searchtext" =>  array("]"), "case_sensitive" => TRUE, "error" => "G_endbracket");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("\n]"), "case_sensitive" => TRUE, "error" => "G_markupline2");
$tests[] = array("type" => "multioccurrence", "searchtext" => "Greek", "case_sensitive" => TRUE, "error" => "G_markuprepeat");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("iou", "uu", "yu", "ôutai", "eôu", "meuai", "siu", "orou"), "case_sensitive" => TRUE, "error" => "G_n_u");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("nn", "eons", "antoi", "nper", "onsin"), "case_sensitive" => TRUE, "error" => "G_u_n");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("aoi ", "ataotha", "ophê", "oin"), "case_sensitive" => TRUE, "error" => "G_s_o");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array(" no ", "oos", "aotoi", "oper", "oosin"), "case_sensitive" => TRUE, "error" => "G_u_o");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array(" fas", "\nsf"), "case_sensitive" => TRUE, "error" => "G_ph_f");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("Ch"), "case_sensitive" => TRUE, "error" => "G_chicase");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("Th"), "case_sensitive" => TRUE, "error" => "G_thetacase");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("ß"), "case_sensitive" => TRUE, "error" => "beta_eszett");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("O ", "on de", "oontai", "eme", "meon", "sphe", "lie"), "case_sensitive" => TRUE, "error" => "G_missingcirc");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("B"), "case_sensitive" => TRUE, "error" => "Brotoi");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("gap", "pep", "pot"), "case_sensitive" => TRUE, "error" => "G_r_p");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("ter"), "case_sensitive" => TRUE, "error" => "p_t");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("ouin"), "case_sensitive" => TRUE, "error" => "missings");
$tests[] = array("type" => "expectedtext", "searchtext" =>  array(".]", "]."), "case_sensitive" => TRUE, "error" => "missingperiod");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("]."), "case_sensitive" => TRUE, "error" => "G_punctplace");
$tests[] = array("type" => "expectedtext", "searchtext" =>  array("tai,"), "case_sensitive" => TRUE, "error" => "G_missingcomma");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array(" oion", " oi", " uper", " yper", " êmeôn"), "case_sensitive" => TRUE, "error" => "G_missingh");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("ö", "é", "á", "è", "ó", "ì", "í", "\\", "/", "^"), "case_sensitive" => TRUE, "error" => "G_extraaccent");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("phopoi", "dhê", "theohus", "tohi", "tiho", "mheôn", "khak", "dhe", "lhi", "pher", "mhoron", "ghar", "kahi"), "case_sensitive" => TRUE, "error" => "G_extrah");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("ahitio", "haitio", "hex", "hô", "hemm", "haut", "ahut", "ahyt", "hatas", "halge", "hecho"), "case_sensitive" => FALSE, "error" => "G_smooth_rough");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("ohi"), "case_sensitive" => TRUE, "error" => "G_rbdiph");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("\"Ô", "'Ô"), "case_sensitive" => TRUE, "error" => "G_smooth_apos");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("êisin", "|"), "case_sensitive" => TRUE, "error" => "G_iotasub");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("kak\n", "alge "), "case_sensitive" => TRUE, "error" => "G_missingapos");
$tests[] = array("type" => "expectedtext", "searchtext" =>  array(";"), "case_sensitive" => TRUE, "error" => "G_missingpunct");
$tests[] = array("type" => "forbiddentext", "searchtext" =>  array("eoys", "aytoi", "oysin", "nu", "huper"), "case_sensitive" => TRUE, "error" => "G_upsilon");
$tests[] = array("type" => "expectedtext", "searchtext" =>  array("toi\n"), "case_sensitive" => TRUE, "error" => "G_missinglb");
$tests[] = array("type" => "expectedtext", "searchtext" =>  array("tai,\n"), "case_sensitive" => TRUE, "error" => "G_missinglb");
$tests[] = array("type" => "expectedtext", "searchtext" =>  array("\nbro"), "case_sensitive" => TRUE, "error" => "P_joinline");
$tests[] = array("type" => "expectedtext", "searchtext" =>  array("\nemm"), "case_sensitive" => TRUE, "error" => "P_joinline");
$tests[] = array("type" => "expectedtext", "searchtext" =>  array("\nmo"), "case_sensitive" => TRUE, "error" => "P_joinline");

// vim: sw=4 ts=4 expandtab