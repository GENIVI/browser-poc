/**
 * Copyright (C) 2014, Pelagicore
 *
 * Author: Jonatan Palsson <jonatan.palsson@pelagicore.com>
 *
 * This file is part of the GENIVI project Browser Proof-Of-Concept
 * For further information, see http://genivi.org/
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

class WebPageGenerator {

public:
    static char *testPageContents()
    {
        return (
        "<HTML>"
        "    <HEAD><TITLE>Browser PoC test page</TITLE></HEAD>"
        "    <BODY>"
        "        <A HREF='http://www.google.com'>"
        "            <DIV style='height:100; width:100; background-color:gray'>Go to google</DIV>"
        "        </A>"
        "        Lorem ipsum dolor sit amet, consectetur adipiscing elit. Fusce ac dignissim leo. Vivamus euismod tortor eu varius molestie. Proin non egestas mauris. Suspendisse nec fringilla mauris, sed dapibus mi.  Mauris suscipit rutrum turpis non venenatis. Nunc quis dolor id massa dignissim rutrum. Praesent pretium enim vitae metus placerat, sed sodales elit blandit. Sed volutpat magna neque, ac mollis velit ullamcorper et. Quisque lorem dolor, suscipit mattis mi vitae, euismod cursus magna. Proin at commodo tortor, vitae convallis ipsum. Suspendisse potenti. Vivamus leo metus, feugiat at elit eu, ultricies mattis ipsum. Ut eros risus, facilisis at scelerisque a, hendrerit id odio. Quisque sapien erat, tristique vitae erat non, venenatis elementum leo. Donec at nisi justo. Integer at fringilla ante, in scelerisque risus. Praesent a leo orci. Donec urna eros, molestie non erat ut, pellentesque faucibus odio. Proin in porttitor erat. Duis ac justo massa. Donec nec augue quis nibh feugiat vestibulum. Morbi tortor velit, malesuada nec nulla ac, semper vehicula"
        "       <DIV style='height:100; width:100; background-color:gray'"
        "                  onClick=\"JavaScript:window.status='browser-poc';\" >"
        "           Set status bar text"
        "       </DIV>"
        "    </BODY>"
        "</HTML>"
        );
    
    }
};
