/*
 * Copyright (c) 2014-2016, The CyanogenMod Project. All rights reserved.
 * Copyright (c) 2017, The LineageOS Project. All rights reserved.
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

package com.android.internal.telephony;

import static com.android.internal.telephony.RILConstants.*;

import android.content.Context;
import android.telephony.Rlog;
import android.os.Message;
import android.os.Parcel;
import android.os.AsyncResult;
import android.os.SystemProperties;
import android.telephony.PhoneNumberUtils;
import android.telephony.SignalStrength;
import android.telephony.SmsManager;
import com.android.internal.telephony.uicc.IccCardApplicationStatus;
import com.android.internal.telephony.uicc.IccCardStatus;
import com.android.internal.telephony.uicc.IccRefreshResponse;
import com.android.internal.telephony.uicc.IccUtils;
import java.util.ArrayList;
import java.util.Collections;
import android.media.AudioManager;

/**
 * RIL customization for Huawei hi6620oem platform
 *
 * {@hide}
 */
public class HwHisiRIL extends RIL {

    private AudioManager audioManager;

    public HwHisiRIL(Context context, int preferredNetworkType, int cdmaSubscription) {
        this(context, preferredNetworkType, cdmaSubscription, null);
    }

    public HwHisiRIL(Context context, int preferredNetworkType,
                   int cdmaSubscription, Integer instanceId) {
        super(context, preferredNetworkType, cdmaSubscription, instanceId);
        audioManager = (AudioManager) mContext.getSystemService(Context.AUDIO_SERVICE);
    }

    static final int RIL_UNSOL_HW_CS_CHANNEL_INFO_IND = 3003;

    @Override
    protected Object
    responseSignalStrength(Parcel p) {
        int numInts = 14;
        int response[];

        response = new int[numInts];
        for (int i = 0; i < numInts; i++) {
            response[i] = p.readInt();
        }

        return new SignalStrength(response[0], response[1],
                                  response[2], response[3],
                                  response[4], response[5],
                                  response[6], response[7],
                                  response[8], response[9],
                                  response[10],response[11],
                                  response[12],response[13],
                                  true);
    }

    static String responseToString(int request) {
        switch(request) {
            case RIL_UNSOL_HW_CS_CHANNEL_INFO_IND: return "RIL_UNSOL_HW_CS_CHANNEL_INFO_IND";
            default: return RIL.responseToString(request);
        }
    }

    @Override
    protected Object
    responseFailCause(Parcel p) {
        int numInts;
        int response[];

        numInts = p.readInt();
        response = new int[numInts];
        for (int i = 0 ; i < numInts ; i++) {
            response[i] = p.readInt();
        }
        LastCallFailCause failCause = new LastCallFailCause();
        failCause.causeCode = response[0];
        if (p.dataAvail() > 0) {
          failCause.vendorCause = p.readString();
        }
        return failCause;
    }

    @Override
    protected void
    processUnsolicited(Parcel p) {
        Object ret;

        int dataPosition = p.dataPosition();
        int response = p.readInt();

        switch (response) {
            case RIL_UNSOL_HW_CS_CHANNEL_INFO_IND: ret = responseInts(p); break;
            default:
                // Rewind the Parcel
                p.setDataPosition(dataPosition);

                // Forward responses that we are not overriding to the super class
                super.processUnsolicited(p);
                return;
        }

        switch (response) {
            case RIL_UNSOL_HW_CS_CHANNEL_INFO_IND:
                if (RILJ_LOGD) riljLog(responseToString(response) + " " + retToString(response, ret));
                setAmrWb(((int[]) ret)[0]);
                break;
        }
    }

    /**
     * Set audio parameter "incall_wb" for HD-Voice (Wideband AMR).
     *
     * @param state: 1 = unsupported, 2 = supported.
     */
    private void setAmrWb(int state) {
        if (state == 2) {
            riljLog("setAmrWb(): setting audio parameter - incall_wb=on");
            audioManager.setParameters("incall_wb=on");
        } else {
            riljLog("setAmrWb(): setting audio parameter - incall_wb=off");
            audioManager.setParameters("incall_wb=off");
        }
    }
}
