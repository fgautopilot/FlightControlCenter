/*
 * Copyright © 2015-2016 Oleksii Aliakin. All rights reserved.
 * Author: Oleksii Aliakin (alex@nls.la)
 * Author: Andrii Shelest
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import QtQuick 2.7

import FGear 0.1
import FGear.Components.Actions 0.1

FgBaseAction {
    id: menuAction
    objectName: "menuAction"

    property FgMenuActionGroup group
    readonly property bool active: group && (group.activatedAction === menuAction)

    property string pageSource: ""
    signal menuSelected(string source)

    onTriggered: {
        if (group) {
            if (active) {
                console.log("[MenuAction]", objectName, "already activated!");
                return;
            }

            group.activatedAction = menuAction;
        }
        menuSelected(pageSource)
    }
}