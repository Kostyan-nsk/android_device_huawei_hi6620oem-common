/*
 * Copyright (C) 2016 The CyanogenMod Project
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


extern int _ZN7android6Parcel13writeString16EPKDsj(void *, unsigned int);

int _ZN7android6Parcel13writeString16EPKtj(void *addr, unsigned int len) {
	return _ZN7android6Parcel13writeString16EPKDsj(addr, len);
}
/*
//-----------------------------------------------------------------------------------------
extern int _ZN7android6Parcel9writeBlobEjbPNS0_12WritableBlobE(unsigned int, int, void *);

int _ZN7android6Parcel9writeBlobEjPNS0_12WritableBlobE(unsigned int len, void *outBlob) {
    return _ZN7android6Parcel9writeBlobEjbPNS0_12WritableBlobE(len, 0, outBlob);
}
//-----------------------------------------------------------------------------------------
*/