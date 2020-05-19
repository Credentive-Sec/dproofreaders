#!/usr/bin/env php
<?php
$relPath="../pinc/";
include_once($relPath."CharSuites.inc");

foreach(CharSuites::get_all() as $charsuite)
{
    echo "Validating charsuite $charsuite->name...\n";

    // Validate that the character suite only contains normalized codepoints
    $nonnormalized_codepoints = $charsuite->get_nonnormalized_codepoints();
    if($nonnormalized_codepoints)
    {
        echo "ERROR: codepoints are not normalized:\n";
        foreach($nonnormalized_codepoints as $orig => $norm)
        {
            echo sprintf("    %s normalized is %s\n", $orig, $norm);
        }
        exit(1);
    }

    // Validate pickersets only contain characters within the suite
    foreach($charsuite->pickerset->get_subsets() as $title => $picker_subset)
    {
        foreach($picker_subset as $codepoints)
        {
            $string = implode("", convert_codepoint_ranges_to_characters($codepoints));
            $invalid_chars = get_invalid_characters($string, $charsuite->codepoints);
            if($invalid_chars)
            {
                echo "ERROR: pickerset $title has codepoints not in charsuite:\n";
                foreach($invalid_chars as $char => $count)
                {
                    echo sprintf("    %s: %s\n", $char, utf8_chr_to_hex($char));
                }
                exit(1);
            }
        }
    }
}