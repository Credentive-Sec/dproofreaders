<?php
$relPath="./../pinc/";
include_once($relPath.'base.inc');
include_once($relPath.'slim_header.inc');
include_once($relPath.'user_project_info.inc');
include_once($relPath.'Project.inc');  // get_projectID_param()

require_login();

$projectid = get_projectID_param($_POST, 'projectid');

$subs = array();
$unsubs = array();
foreach ( $subscribable_project_events as $event => $label )
{
    if (!can_user_subscribe_to_project_event( $pguser, $projectid, $event ))
    {
        continue;
    }

    if ( @$_POST[$event] == 'on' )
    {
        subscribe_user_to_project_event( $pguser, $projectid, $event );
        $subs[] = $label;
    }
    else
    {
        unsubscribe_user_from_project_event( $pguser, $projectid, $event );
        $unsubs[] = $label;
    }
}

slim_header(_("Event Subscriptions"));

_html_ul(
    _("You are now subscribed to these events for this project:"),
    $subs );

_html_ul(
    _("You are now unsubscribed from these events for this project:"),
    $unsubs );

function _html_ul( $header, $items )
{
    echo "<p>" . html_safe($header) . "</p>";
    echo "<ul>\n";
    if ( $items )
    {
        foreach ( $items as $item )
        {
            echo "<li>$item</li>\n";
        }
    }
    else
    {
        echo "<li><i>" . pgettext("no subscriptions", "none") . "</i></li>\n";
    }
    echo "</ul>\n";
}

echo "<p>" . sprintf(_("Return to the <a %s>project page</a>"), "href='$code_url/project.php?id=$projectid#event_subscriptions'") . "</p>";

// vim: sw=4 ts=4 expandtab
