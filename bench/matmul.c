#define N 32
#define B 8

static inline void matmul_block(int *a, int *b, int *c, int sk)
{
    for (int i = 0; i < B; i++) {
        for (int j = 0; j < B; j++) {
            int cij = sk == 0 ? 0 : c[i * N + j];
            for (int k = 0; k < B; k++)
                cij += a[i * N + k] * b[k * N + j];
            c[i * N + j] = cij;
        }
    }
}

static inline void matmul(int *a, int *b, int *c)
{
    for (int sj = 0; sj < N; sj += B) {
        for (int si = 0; si < N; si += B) {
            for (int sk = 0; sk < N; sk += B) {
                matmul_block(a + si * N + sk, b + sk * N + sj, c + si * N + sj, sk);
            }
        }
    }
}

static int a[N * N] = {
    0xa64b0cd9, 0x7259e4f2, 0x05ed01f1, 0x958e3cd3, 0x24d2b530, 0x970abf93, 0x9a77d3dc, 0xf71295af, 0xe633dc78, 0xbfc18778, 0xe10b4ce3, 0x6c2e8f0f, 0x76a21736, 0x83d5228d, 0xb88623f7, 0xcecc1d25,
    0xae06ab6a, 0x2682571f, 0x76c20050, 0x76eac5b0, 0x7c94fc32, 0x2ddd1314, 0x75be43b7, 0xba9efb4d, 0x19b45ffa, 0x29f53edd, 0x6dfe83d8, 0x16e74a9c, 0x7005546a, 0x05fac9d7, 0xdee613b7, 0x08e82bc5,
    0x853697a9, 0x0e108173, 0x620031fc, 0x1a21d1f4, 0xe4878835, 0xfc1c0b50, 0xdaa0937a, 0xa2b652a6, 0xe1a5f9d7, 0xf65ac7d8, 0x38ab93cf, 0x01a9cbec, 0x6b231301, 0xc3f090fc, 0x325b2a70, 0xab1a1f63,
    0xe1631536, 0x6070581f, 0xe9193e3e, 0x0ab7e796, 0x4a0b6fa1, 0x944d8d2c, 0x07b7716e, 0xecaf4d9b, 0x17d61dbf, 0x907a28ab, 0x9d9047ae, 0x0b2a96f3, 0x67b93862, 0x677390d1, 0x0124d486, 0x6da104f1,
    0x0ef74bce, 0x10a89fb3, 0xd18844f1, 0x934ce344, 0x7d28179a, 0x630e2596, 0x027bc814, 0xfd4b8389, 0x34d011bd, 0xc8dfaa0a, 0xaf0b35cc, 0x961024dd, 0x849c17ab, 0x35923b96, 0x57c3ecf5, 0xcd624783,
    0x23d780ab, 0xad07fcc2, 0x54b5b196, 0x01c9e285, 0x1b641ea1, 0xb7193a9f, 0xe78267f4, 0xa57fe1d1, 0x9bd1965c, 0x7552deba, 0xd3f106cd, 0xb07e8d0a, 0x73d50e6a, 0xcdbbcb29, 0x401d3826, 0x852ddc68,
    0x2cb974c9, 0x89628a12, 0xa05f1570, 0x7f6c395f, 0x53d28eb8, 0x3c47f7bf, 0xf2297250, 0xc5df38c7, 0xeae5e053, 0x96b66666, 0xec78e58a, 0xef6f78c2, 0xbda8edb3, 0xadbd7944, 0x4365ff02, 0xcb99b0ae,
    0xd6a4d193, 0x00c75b86, 0x09acb53c, 0xd46d3826, 0x5ae45f56, 0x6ec443a4, 0x1f534a06, 0x6e655324, 0xd33e4fc7, 0x05fd998c, 0xa6b88354, 0x8646f6b4, 0x94ff3275, 0x362edafc, 0x01de58d2, 0x0ee6d614,
    0xaa18ded2, 0xbe3fa2a6, 0xf484c0e4, 0x136e7ba2, 0xd2e31e05, 0x7af9eb39, 0x52f118b6, 0x6a64d61d, 0x6337b7a4, 0xa1212a84, 0x782d2bfa, 0x9f279273, 0x8ff2e1a5, 0x2858e1b1, 0xcf7c1099, 0xc80abc25,
    0x26867cd8, 0xa90132c8, 0x95df89fb, 0xeba4fa64, 0xf36114e6, 0xfebb840c, 0x2e2ffa8d, 0x70eac618, 0x290629ad, 0xe162de44, 0xbc56d5b5, 0x4f706772, 0xe912492e, 0x80380621, 0x45e100f1, 0xebec505b,
    0x0b7e32cc, 0x5929d362, 0x18e1dbe5, 0xab87efca, 0x18a017cf, 0x6aa95f80, 0xe1f00219, 0x7d99d703, 0xffddfee1, 0x62edb799, 0x53332276, 0xc554547f, 0xd29b959b, 0x72e63d40, 0xbabac56f, 0xc37653ad,
    0x53e79416, 0x7e8494fd, 0x8845ac9e, 0x331ff571, 0xdc0656ad, 0xc015b8bb, 0x3a66289f, 0x440d4661, 0x0b4246de, 0xb396598b, 0x25d08869, 0x07a067dd, 0xb61614f0, 0xd6ee7e9f, 0x4b32e94f, 0xef7d2863,
    0xb62f6b77, 0x1c2e4f6c, 0x29167e21, 0x15e47051, 0xdab4c90a, 0xf2661f3d, 0x05f03bdb, 0x5453225d, 0xd06c575b, 0xc4f5aaa9, 0x63361f1d, 0x9c9a7aef, 0x1ef3028b, 0xbb249a4c, 0xe2da3c2d, 0x486cee34,
    0x1632f3f8, 0x364380ad, 0x40b77ea0, 0xc32b309f, 0x41315739, 0xcf217058, 0xad0ec8bc, 0x7f415306, 0x8caf67ad, 0xbe1f6be3, 0x3a66067b, 0x4182d9f0, 0xdb02d8f9, 0xa4deadde, 0xa6f80108, 0xfca258ff,
    0xac585a1a, 0xa6d63f80, 0xa527a5de, 0x64cd7783, 0xfd394e7f, 0x61b96e6b, 0x8345c0b5, 0x1ac903f2, 0x7747e307, 0x33fe708b, 0x8f5bf704, 0x889fe682, 0x54d49613, 0x0f3eb1de, 0x0862374e, 0x462eb192,
    0x4c439bce, 0xed8c97fa, 0x5ed7b5b8, 0x25ac47df, 0xe373114d, 0x260f3e92, 0x6b855cad, 0x05071fa7, 0xade9cbd7, 0xab3286d4, 0xf59d75bb, 0x8c033fc4, 0x04df08fa, 0x9981e1d1, 0x7cca694b, 0x8a54dafb,
    0x5974c67e, 0x316d8954, 0xa83066a4, 0x16181fd2, 0xd55cebfb, 0x2f86866a, 0x9bd0cfe4, 0x64c43419, 0x01ed1302, 0x72b7aba6, 0x57222ce2, 0x5b84f8fc, 0xfb8874c9, 0x8bc3f046, 0x704c8258, 0x4aba4684,
    0x44f11013, 0x96fb03b3, 0x91c1aa36, 0xd7ee4d52, 0x9e29e8f4, 0xe9d61d06, 0xa0c6951c, 0x593329d6, 0x49d6a133, 0xb331b063, 0xddb23061, 0xe964f918, 0x250284fb, 0x7c1d3c9d, 0x6f7900fc, 0x1edc8241,
    0xd77135bc, 0x758f41d6, 0x17d9180b, 0x0137ac06, 0xb11f36dc, 0xa4f649df, 0x305288b8, 0x1d579346, 0xb77c0660, 0x3f10f10b, 0x267fce32, 0xa8dfe3d9, 0x4858a9d8, 0x25cfee27, 0xe35bdb32, 0x13e40254,
    0xbb7ecd4c, 0x33b87ecd, 0xd1dcc439, 0x970e2a6e, 0x582cc7be, 0x5d44ab22, 0x610792f9, 0x4ce8e869, 0x56e37499, 0x30945e5d, 0x51737d9b, 0xcbc7bf76, 0x3c0f2e41, 0x09374a74, 0x04a43251, 0x01441d0f,
    0x3f10c4a1, 0xa77f15ff, 0x1f08d704, 0xc169a3cf, 0x5c51248c, 0x6e57cdd9, 0x172ece08, 0xfe8fcfa7, 0xbbbbe380, 0xa9b4773a, 0x87882e69, 0x5844da41, 0xb57d9b1d, 0x205ef6b3, 0x0481416a, 0x4beacfde,
    0xa190628a, 0x0cce20e1, 0x17ed7a8a, 0xb948c4c4, 0x094aa3b1, 0xc974da3c, 0x579b27bc, 0x5a59cf58, 0xb3256c05, 0x206e85c2, 0x13257559, 0x97da15b1, 0xaf0d05f3, 0x93942144, 0x150707ec, 0xbe40a7db,
    0xc1a3ce69, 0x99f10620, 0x66a05bd2, 0xe2b8e598, 0xe14f7427, 0x5f5aae88, 0xd9f113a7, 0x10476bfc, 0x836745cc, 0xfc7420cd, 0x1965b244, 0x6fce30dc, 0x2cba4d09, 0x486869ac, 0xfb597da5, 0x424dedab,
    0xd7737274, 0x0f7a84be, 0x65180c94, 0x03d8124d, 0xa581edf2, 0x9bfe30cc, 0x0f2b7d1d, 0xffdfda70, 0x4746f719, 0xb6c678b9, 0xbe6b5608, 0x4eb4cecf, 0x969ed52c, 0x14a64640, 0x7a71217c, 0xd6b90ebf,
    0xd8453e93, 0x68d1fc7a, 0xe304fa36, 0xb07e5c8d, 0x0e6e511f, 0xff9faecd, 0x76621428, 0x3b69902e, 0x0e25ef02, 0xfdae2cb7, 0xab40495d, 0x2a53c6d4, 0x72666311, 0x5c49f031, 0x7757905a, 0xb8235dc3,
    0x89dc0ac3, 0xa38ceff5, 0xc572b2a8, 0xa8e1ee67, 0xe01dbc68, 0xdb3925ca, 0x287cfe5b, 0xac80f583, 0x7890898a, 0xddbac304, 0xa0e959ad, 0x91cbc3e8, 0x78a961e4, 0x5cedb494, 0x448c3146, 0xed6c1c91,
    0x5f55f73f, 0x61bca6ae, 0x4fe9cecb, 0x0b19dfa1, 0x9df15287, 0x4762d84a, 0xb3625feb, 0xc85b05c2, 0x430a097e, 0xc48efd64, 0x8abd0667, 0x1f539eb6, 0x31e7a515, 0xcd7de4df, 0x3a372f8e, 0x532e5405,
    0xeaa9a8a0, 0x1d49533f, 0x89ea822d, 0x82ea7dbb, 0x79388866, 0x145172cf, 0xb88d34a3, 0x2f57b344, 0x9abcb121, 0x746dce55, 0x52ed2245, 0xc35ed336, 0x0055c0be, 0xbad105f5, 0x9ca41b3f, 0x4ce8dde8,
    0x3aba7bf4, 0x7e195fdd, 0x4897e7cc, 0x8d0c2eda, 0x04aad558, 0x9230a683, 0x667fb37b, 0x681bd3a6, 0x44af4636, 0x421bde45, 0x09304eec, 0x8dce4a47, 0xbbcfc5e1, 0x25a0e9c4, 0xd6d8cabe, 0xd2b19246,
    0x8226b812, 0x96353573, 0x7890733a, 0x8df68b96, 0x964fad2c, 0x56f765ad, 0x0870cddf, 0x2e8a4514, 0xfd806bff, 0x01466d07, 0xe3137a3b, 0x47bc4757, 0x85af87d6, 0xb9f04a9f, 0xac9d4a7e, 0xbf24359b,
    0x4ba5117a, 0x429275df, 0x90963f8c, 0xfe70d1a2, 0x52db4316, 0x79ec8cb3, 0x97deae47, 0xe8cf48cc, 0x657b7e52, 0xc1951e8a, 0x303f3347, 0x7aafc84d, 0xa08f1b0a, 0x2df285e9, 0x260bdead, 0x53a38e62,
    0xd404312c, 0xc7857abb, 0x20a5f1a9, 0x5cfda6dc, 0x9c4951c6, 0x34bd47db, 0xfb93f99e, 0x5343568a, 0xfef62144, 0x84fa56c6, 0x556a38eb, 0xcf2c168e, 0xc1ffee17, 0xe9bdb5e7, 0xce084844, 0x2cae4aeb,
    0x05af6397, 0x33ecf395, 0xeb7b2194, 0xeca1bc2a, 0x52b7bc38, 0x133d2f83, 0x2075af83, 0xee77d3ef, 0x78739f03, 0x25f78880, 0x826e544f, 0xa02bc3a3, 0x3dcaa188, 0x70b19e22, 0xfed4ee7c, 0xae931926,
    0xdaf25926, 0xbd7d96c1, 0x9c8eda00, 0x1d06c4ee, 0x804ab115, 0x1d685073, 0x33c3e230, 0xa9528fe1, 0x5c0aef15, 0x192e26c9, 0x8f7e6ac6, 0x3bc37fc1, 0xe926f0b3, 0xa14c5e37, 0x7a329e40, 0x899a8648,
    0x59def8cd, 0x86693997, 0xab693298, 0xd0108ad7, 0x8e99f591, 0xb08289a5, 0x9e608fa0, 0x6e36cc20, 0xbee56322, 0x9a04c93f, 0x319b9ea1, 0xea36eca8, 0x7c44f980, 0x446bf76c, 0x2df2f482, 0x591923cd,
    0x59f1d6d1, 0x993172ca, 0xb751d13b, 0x5702c5bb, 0xf2b62f20, 0x2590c0d7, 0x5b7a66f1, 0x5dd28e90, 0xac0bc29a, 0x57b46dbe, 0x141b32d2, 0x284847ee, 0x03c678ee, 0x883269b5, 0x58e1782a, 0x2d53d6b2,
    0x028b12ae, 0x8c1e4133, 0x8d6a34e8, 0xe36ab519, 0xb3bf9cfc, 0x935293dc, 0xcb3c5f3e, 0xf253ad45, 0xd47d68a4, 0xfdc71ce3, 0xd8cd3346, 0xb6b346ae, 0x529835bb, 0x9cef442c, 0xda2605c9, 0x191e5791,
    0xbf7fb9b3, 0x8b12612f, 0xf8d44112, 0x07dcc9de, 0x06ef0337, 0xb85b9221, 0x14998a2f, 0x3a6b03dd, 0x3d33f60e, 0x7c6ecd32, 0x9a454fa9, 0x8672933d, 0x23314bbc, 0xf22efa4a, 0x4010b614, 0x4a4c68d7,
    0x4266e6d1, 0xdd42b778, 0x8cbba42e, 0x4c62ebf8, 0xf67d3c29, 0xbccc227b, 0x7341637d, 0x0ae54b6d, 0x73405e7c, 0xa5ddac9f, 0x656c7da6, 0xed8f721e, 0x6e467221, 0xc1a6a3c9, 0x273c964d, 0xaf8ca4d3,
    0xcfcf7f12, 0x6acc442e, 0xac72c800, 0x3664fcc9, 0x226b8025, 0x6c730e0b, 0x097a8a83, 0x6524f3fd, 0xbc8d8ae2, 0xb1dcd143, 0x6ae9bbd0, 0x0215885d, 0x95ffe44a, 0x78163928, 0xb172a780, 0x4018ba02,
    0xbad92aab, 0x45f42e42, 0xd5f63ae7, 0xd1905f3c, 0x571afce9, 0xb5d316f3, 0xcf288e7c, 0x5365d311, 0x62144f90, 0xb9fe8bcc, 0x28805208, 0xcc12932b, 0x2cac014c, 0xc295da1b, 0x6d5a3767, 0x2942363c,
    0xa9785e14, 0x645c73c5, 0x2a21ec1e, 0x94b97407, 0xca3fc0ef, 0xff1ca3ee, 0x7d3de9c6, 0xde315f81, 0x3bc73f53, 0x0baff9fa, 0xa8b64344, 0x7fbde281, 0x36052800, 0xec85972b, 0x6a08c166, 0xc1db2207,
    0xdbac30ed, 0xa174cdf8, 0x0dae5bce, 0xa0a67e62, 0x28c8c81e, 0x79d226a9, 0xfed016ad, 0x8eb5ec5d, 0x1a590dd7, 0xf5f7e0df, 0x9c04cc84, 0x5767d330, 0xb544d5d1, 0x65274b3b, 0x2f0c72b1, 0x75435a9e,
    0x731c6bf7, 0x3a4f1024, 0x491a88c0, 0x4dd30a60, 0x89a61696, 0x3832e69d, 0x8658f9ce, 0xbb3e1f76, 0xb121b770, 0xa7dc935a, 0xf8f78b08, 0xfd69c040, 0xb02feec7, 0xbedf1920, 0xe1872db5, 0x5c72b238,
    0x9a3c4c31, 0x7c32d60b, 0x34a3543e, 0x09c45c04, 0x970b206a, 0x94d465f9, 0x30cafeda, 0xf438ef32, 0xe014f860, 0xf92b0849, 0x5ad6b811, 0x28285841, 0x27507b45, 0x9a868c55, 0x9fb547f3, 0xfbf323ad,
    0x7e0ed222, 0xdcc536c0, 0x501fc816, 0x0f427de3, 0x726326c7, 0xffb75ce8, 0xe0b7d626, 0xa59fddd8, 0xab11d128, 0x0bbb49ed, 0x1c000ea7, 0xc10517e8, 0x6a5e0d2d, 0x63e35583, 0x4957fb40, 0xd83da19e,
    0xe5868866, 0xb9a1d7fe, 0x4ac2af67, 0xe37bce57, 0xa11b18ac, 0xe27373b4, 0xd3c40380, 0xb5d15be9, 0x2ab2462c, 0x4f7224c5, 0xf7e0b4ee, 0x40bcb875, 0x99297492, 0xa4b56bdd, 0xb501b612, 0x222ecd6b,
    0x95c261d8, 0x4308eeb8, 0xce06120c, 0x5a3a97ae, 0x75dacef4, 0xa5793e00, 0xfce20268, 0x1d775a37, 0x15c75579, 0x34bacc0b, 0xdac368ea, 0xda5ccfc4, 0x9abfdfc0, 0xc49e5872, 0x61b3de5f, 0xff8f7b4a,
    0x8fa2f8ac, 0xa69cbf2c, 0xfecf0e03, 0x8eab50e5, 0xbbf0128d, 0x3662e370, 0x603cc5c1, 0x8e5573bf, 0xecf19550, 0x34d22812, 0x1ab3ef11, 0xe9a8c2e6, 0x9b41991e, 0x4f26e6cd, 0x149aea53, 0x9bd7e312,
    0xcae5cac7, 0x8185a15c, 0xf8cc9854, 0xf0b03f1a, 0x226e4fcd, 0x15f6f944, 0x36a4e29c, 0xfcfb5a0a, 0xdf6a9616, 0x08a469f6, 0x56561478, 0xa09b9d1e, 0x11b53a45, 0x75d4eb95, 0x587a876d, 0x1b48a7c5,
    0x113da61f, 0x4e1164e1, 0x85e859f0, 0x37109b3d, 0x9d4e5319, 0xf482f82e, 0x183ea305, 0x31afde49, 0x33fc226d, 0x67aada95, 0xbdc1e125, 0x73e150a6, 0x0a6c1b21, 0x3d8ee4ab, 0xf6152cf8, 0x51c6cf27,
    0xdefa7f51, 0x659a2605, 0xefe45cdd, 0x54c3e5ee, 0x83e9f188, 0x8b1d0cc1, 0x09d81b75, 0x840dd96c, 0x3b4d2c0d, 0x55c83234, 0x42dacc6e, 0xf2b4c3b6, 0x2b119702, 0x745ae959, 0xb02824c8, 0xaafb241d,
    0x7d4be35b, 0x775ed164, 0x2b3c7d92, 0xb7f5f8b0, 0xd4f457ca, 0x108b9df0, 0xb4382cd0, 0x5a7009f2, 0xc9a97d77, 0x05ccf0cb, 0x03570c30, 0xbbdeefeb, 0xba262927, 0x72e5d78a, 0xb78c31db, 0x75c264cf,
    0x22907d2b, 0xbe346ebd, 0xc4f0dd5b, 0xf79bc550, 0x533b800d, 0x3bd65bfd, 0xf59893fe, 0xad3a8920, 0xb5315c2d, 0x8e69ed07, 0x27b1e736, 0x3b3bfe4a, 0xe9f5697d, 0xa09612e0, 0xff7c90f6, 0x5355e51c,
    0x701f8900, 0xe97c6c5b, 0x70ece321, 0xcaa7aa45, 0xdb02ef31, 0xb0b30b03, 0xb15ec0a8, 0xc51ecc5d, 0xc5e3c46c, 0x5757cfdd, 0x2fc87e14, 0x28036695, 0x4ca72c23, 0x3eb76422, 0xc98fbd6c, 0x053d50c0,
    0x6a4d772b, 0xe9d8c1eb, 0xf2ecba75, 0x730928b7, 0x1fdb2dd9, 0x3492d890, 0x3ba68ad7, 0x9f1ad483, 0x78a71bb8, 0x81003d23, 0xc766049d, 0x203fe709, 0x7c1a2034, 0x7f5fa05e, 0xf7a8b770, 0xb29b5b89,
    0x58ab7d95, 0xbdebda4f, 0x6190af71, 0x3af2857b, 0x5905b4b1, 0x0ad16c8e, 0xd85b46fc, 0x2717e3fd, 0x7ce70c25, 0x4a9ab406, 0x27bbc102, 0x927bdf29, 0x651e5ff2, 0x5872ca0a, 0x23150f6a, 0xc533d4d9,
    0x619d1580, 0xccaa7e15, 0xffe8375f, 0x4c9c61af, 0x44f54462, 0x1cf65145, 0x2a6c558a, 0xa5bbef59, 0x55e646b9, 0x5d1ca01a, 0x48b326b7, 0xa866d837, 0xec9b473a, 0x146f29db, 0xddeaa91b, 0xa14cd90b,
    0x12c5824b, 0x43bbf747, 0x66fe2bb0, 0x5df49688, 0xfe2da3c6, 0xcf525ede, 0xe3c5a8b0, 0x8e1945f5, 0xa667cb42, 0x1191a878, 0x94532f8e, 0x628e74ff, 0xc322ade0, 0xeee2c5f6, 0x46ca35d2, 0xaa7025f9,
    0x4b9accf2, 0x9e87e3d7, 0x926b6daa, 0xc6a5fce9, 0xc8ea1b28, 0x3f8e839a, 0x1ae30f44, 0x1db6bb09, 0x7ab45093, 0x028402d4, 0xde94cfef, 0x95172dbf, 0x1156c10b, 0x316153bb, 0xcc81929c, 0x351e4548,
    0x5813f53c, 0xe15629f0, 0x45898053, 0x382196ea, 0x6ea4f581, 0x37d47a5d, 0x2095b6db, 0x483c90d3, 0x90572666, 0xa4649449, 0x4b3a5169, 0x0beeee8e, 0xbaa3a615, 0x1874a9c1, 0x297cdba2, 0x3a1360ff,
    0xf59d1dad, 0xad2bd8fd, 0x8e89c2df, 0x760e84aa, 0x8d297e50, 0xfcd12ba8, 0x7377ae7e, 0xecec8695, 0xcbdbe573, 0x9438d0c7, 0xd2341a72, 0xbcfe00a5, 0xe20faf24, 0xe6f04920, 0x56ef3091, 0xc347c8d6,
    0xb86e4b15, 0x8aaa9fa1, 0x6f74ceec, 0x33e475e2, 0x7a35c0d6, 0x5e1c02d0, 0x455359b0, 0x7b8e878f, 0x77145556, 0x1025d00a, 0xef8f04a6, 0x28d76942, 0x9f948c1e, 0xb41b18ed, 0x41e9de3a, 0x834c8edc,
    0xec723d95, 0xf7d03cd8, 0x525f59f4, 0x433207c7, 0x45e84e42, 0xffa9ec3b, 0x6cc3358a, 0x5f11ccff, 0xfb07d889, 0x61207b3e, 0x60800d66, 0x4559fb70, 0x0cb8e2d3, 0x5a857e82, 0xe2d262f9, 0x5cb65b15};

static int b[N * N] = {
    0x0241c532, 0xb06c3be3, 0x7d9514e8, 0x5af1710f, 0xd0f7fa65, 0xb8aea0d6, 0xb1cc1f93, 0xd1b659db, 0x3db1508b, 0x8903781e, 0x04ee7665, 0xf842d84a, 0xba4639cf, 0xa61bac2f, 0x3d840109, 0xcc177624,
    0x56b70762, 0xca68f31a, 0xb5a66bef, 0x3fd8a603, 0xe4b19fd4, 0x64edea51, 0xb2284b26, 0x80c3d927, 0xa90cc41d, 0x9cf5fbac, 0x60e0216c, 0xf2469d29, 0xf83afabe, 0xddf94ab6, 0x42ec3b85, 0x6d0f1d00,
    0x654ef040, 0xe57437bf, 0xf800081d, 0x7a250541, 0x0ff4c468, 0x241a400a, 0x82769cc8, 0x7a72f415, 0xcf90551c, 0x7bd86c09, 0x90dbc543, 0x64852a18, 0x74fa2d5a, 0x6bd08ea5, 0x48b1c9ce, 0x9a698d99,
    0x8da6a460, 0xa58e1c01, 0x83b0abe6, 0x22576877, 0xbcac9976, 0x6c4a62ad, 0xe7855715, 0x9a36e3fd, 0xcea19919, 0xc1e48d40, 0x162aa3c9, 0x8b755245, 0x3a8d7d9f, 0x50de8489, 0xe3a9f886, 0x598e4448,
    0x70053d45, 0xc0a10f65, 0x4acce2ea, 0x8ec9f015, 0x1b3bc71c, 0x75839f4d, 0x846f086b, 0xc4b9fcd1, 0x25a43ad3, 0xf092fa90, 0xf1a45f1e, 0xbfaba4d7, 0x305500b8, 0x2167b7ff, 0x44fc8e00, 0x4dc9bd59,
    0x26310ed7, 0x920b6870, 0xb29e5509, 0x7a62d5c7, 0x05a2c6ae, 0x81ce5d8c, 0x0bb67500, 0xd1bdfc36, 0x81b61d87, 0x1a8cf6c4, 0xecee7a46, 0x9cf9eea3, 0xb114a318, 0xdfb92978, 0xaebf97aa, 0x048c2e3a,
    0xc37a2fa1, 0x7c414bd2, 0xe6d1f3f4, 0x2bd1113b, 0xf383b3e5, 0x336c6c61, 0x9ccd8d95, 0xf7378a0c, 0x03a611eb, 0xc2a85db4, 0xc29a7478, 0xcdcfb218, 0xcc9c2e9d, 0x4c71a32e, 0xc1437e4f, 0xcfbb7146,
    0x0b715153, 0x1370cea8, 0x12a4a2ef, 0xf2adfc7b, 0x71b70248, 0xf7dd85fe, 0xffcc1e04, 0x478f066c, 0x4f4d8077, 0x384f7856, 0x9cd87dde, 0xf18131a1, 0x55ff054c, 0xc0731d02, 0x2d4b75d1, 0xd30b9fbd,
    0x0dd267a0, 0x3d084a3d, 0x783c5cfe, 0x45ba3575, 0x1690609c, 0x492ec7f2, 0xdb5a0c9b, 0xbf3ab1db, 0x3820c4b4, 0xd3d08829, 0xb5eb6e4d, 0xca39500a, 0x14749b3c, 0xb3124fdc, 0x52187e8d, 0x80beac57,
    0x049c87f2, 0x905e92f0, 0xab7d2783, 0x51e25358, 0x22aaadc7, 0x83741f04, 0xe4301d61, 0x2262c481, 0x7034490f, 0x81c53ff7, 0x86aa23ac, 0x803f7d15, 0xe9b7018a, 0x963c2ec0, 0x56f49ebb, 0xe103f6af,
    0x8b6d6e97, 0x3e08e75e, 0xafd73d82, 0xc34b1e10, 0xe29b57ab, 0x5c2287b7, 0xdb7d45d0, 0x7f6f9367, 0xc18b8255, 0x260ccc4f, 0xb2edd9e1, 0x8c6d0252, 0x64a91a89, 0x330b2355, 0x8bc0e7b3, 0xd0195328,
    0xe679aa46, 0xe94f456f, 0x813a5c50, 0x4a5e037e, 0xc57edd4f, 0xcfea659a, 0x27c3f1c0, 0x7e0baa17, 0xe9aea761, 0x37daf1ff, 0xea7a214e, 0x14713cf4, 0xacfb24e8, 0x6b56f475, 0x282649ba, 0xdcbf208b,
    0x9b5d5257, 0x1eb63e01, 0xbc9e49c1, 0x556fd14f, 0xdfa170de, 0x88ab9529, 0x1030ca4a, 0x404f38b8, 0xf21e43b6, 0xe2238383, 0xe7ba4ffc, 0x073363a3, 0xb1740a08, 0x9dafc5cb, 0x7caa0c95, 0x7c2323ee,
    0xf797fe5d, 0xf5497a81, 0xa6a87b46, 0x0b29c49a, 0x776b0c4b, 0x0cc851a7, 0x764e7726, 0x82b43b81, 0xc8228ac4, 0xc0413e11, 0xeb9a7aa2, 0xe93f6922, 0x80c9c459, 0xb9b0bbf3, 0xc58939f3, 0x62359497,
    0xc4ad078d, 0xf70ad97b, 0x5eccb11e, 0x7c21e69f, 0xdb956c77, 0x67ccd92d, 0xc70aedfb, 0xb7d81d28, 0x16c8b764, 0x1a2e422d, 0x1c52fcfd, 0x64a3646d, 0x689546b5, 0x1aec63d4, 0x082c35e0, 0x58ca0e40,
    0xf16062b1, 0x938685c2, 0xfcbb8822, 0xa1b03108, 0x5a38addc, 0xdb6219b9, 0x73b91992, 0x800329ba, 0x96c2acbd, 0x873c93da, 0x8ef7ad1c, 0xe1654694, 0xf67448c1, 0xdf679fc4, 0x68c078d3, 0x2dc1ebf8,
    0x746067a7, 0x320cbf20, 0x0bf08e4b, 0xcf2a0bb1, 0xc40c7474, 0x022455bb, 0x17eafe56, 0x1298ccd1, 0x5e563f0e, 0x3aa0c5ac, 0x875b9fb5, 0x114f2d45, 0xde0ed5f6, 0x8fd809a6, 0xfc5f0caf, 0x57a6c4e0,
    0x6c91254b, 0x582f27f8, 0x8ac7b96b, 0x4dd83162, 0x85591601, 0x315d0bd7, 0x6756ec35, 0x1ac222bd, 0xbb5a459b, 0xb8750424, 0xc676a10e, 0x368aa176, 0xd856e849, 0xb16f1b24, 0x904fe498, 0xa52b0426,
    0x4ac886bb, 0xead842b0, 0xfacd06ca, 0x21a02f0e, 0xab60272d, 0xc46e4217, 0x3bcff912, 0x050e79dc, 0x3ce68709, 0xce697509, 0x9fa9c68f, 0x8102df36, 0xfc2b4013, 0x8cc7d7bc, 0x176aac35, 0xaa931ee2,
    0xeb6a4109, 0x423781b3, 0xf810acd1, 0x09850bce, 0x80c97bec, 0x0103991c, 0x49e773f6, 0x3210009e, 0x0481f9d4, 0x3d591231, 0xdfbd8868, 0xd7b05744, 0x31952783, 0x7ea2a862, 0x847acdad, 0xf6bee3db,
    0x46d09a34, 0xa575615d, 0xfc7d06bd, 0xf85299de, 0xf771ebf1, 0x7922d806, 0x6bc57858, 0x26a7ce76, 0xaa05482b, 0x99062d6a, 0x5e06c3a3, 0x4d15b567, 0x49ae0386, 0x81a374d0, 0xb40f4d77, 0x84e56dee,
    0xfba88fa1, 0x7410bd4a, 0x5219328f, 0x129f2a1d, 0x2c310e49, 0x104df178, 0x3460873d, 0x1bd7314a, 0xbf90f93d, 0x4e01c2a5, 0x8d3c7813, 0x85057914, 0xefb9d964, 0xdcdb5283, 0x97ca9624, 0x370a9c7f,
    0xad84abf9, 0x9d39a092, 0x4a45aa01, 0xbe79a0fb, 0xb20f13b0, 0x7d0cc4c9, 0x90c80f46, 0x1f776594, 0x05080493, 0x6e60fcec, 0x58fb2e8a, 0x3d83b64c, 0x9473934c, 0x4da857af, 0xb25becac, 0xd48ed6d3,
    0x59c44d3d, 0x7d16477d, 0x1a343b01, 0x8786b175, 0x62dec7f0, 0x0a5ebaea, 0xdad12a48, 0x6f8114cb, 0x73c7818d, 0x439b00f7, 0x28b08e87, 0x9f18bbc2, 0x28b70fe6, 0x211f5cc8, 0x1ab0dfcd, 0x8f1c4a5d,
    0x543f0cfb, 0xf37e1ece, 0xabe23191, 0x69c666be, 0x0b3e98a4, 0xb2aec280, 0xa64dbe2f, 0x0da28632, 0x55668c48, 0x859d957d, 0xd72a3e8e, 0xd0d0e2d5, 0xb0ec1a22, 0xc02fa628, 0xb4564cc9, 0x3a5958d4,
    0x48f584a1, 0xc72314db, 0x04ec5232, 0xab6326ca, 0x8c1e7945, 0xf0d3f491, 0x2acb3071, 0x22690e63, 0x33c84551, 0x2940a4c8, 0xacb537b7, 0x59e9b664, 0xb925bd4e, 0x8e254646, 0x2d99f750, 0x9ef52424,
    0x591f9a34, 0x1a25c237, 0xb43ea9ec, 0xad0244d8, 0x7ae66364, 0xaa94e4cb, 0x14e70b3f, 0x0f4953f0, 0xa3c67d3c, 0x717fdf0c, 0xccc9cd4e, 0x397473f6, 0x0ebacbe5, 0x1ba69d9d, 0x5ab48821, 0x87f8c610,
    0xc22d7f32, 0x5d15d34b, 0xb5125848, 0x8ce3bf35, 0xdd7f71bd, 0x3050e5b7, 0x8c20e05d, 0x4d1013b9, 0x5b654bd1, 0xb6fdcf84, 0xd11e62f7, 0x10bc0b7c, 0x26aada16, 0xc8ac8ec3, 0x65711161, 0x846cd2fa,
    0xcf451f37, 0xa4c18cbc, 0xbd72ecef, 0x4d568eb5, 0x3d5bc26f, 0xc3a67424, 0x8c55ad59, 0x22dd5bbe, 0x83587f65, 0x69aed149, 0x02ec1e68, 0x003e0344, 0x3b9fe579, 0x5b35b93d, 0x25ad8481, 0xfeccc18e,
    0x1a51eaa8, 0xc63dd880, 0x6ae30759, 0xd42c0395, 0x070f726c, 0x8bc0c172, 0xb711ef56, 0x0a01e33d, 0x1de0f79b, 0xf927d08a, 0x324ebbd8, 0x89283424, 0x4d133e4a, 0x9ffcd923, 0x38673277, 0xcfb56484,
    0x17648bbb, 0x3a68397f, 0xd6bfe76d, 0x33b4ff51, 0x7f4b6e05, 0x9d0883e3, 0x68275454, 0x1bac834e, 0x4383f79d, 0xaa1159c6, 0x32db1f3b, 0xbd700353, 0x9d2a40ac, 0x8010a795, 0x84e1b267, 0x6130d994,
    0xc9d5cf79, 0x903596c0, 0x7bee2ec7, 0x04d9dbda, 0xd61ba21a, 0x2f702704, 0xe466a064, 0xf4d475d4, 0x7d8db3e4, 0xedd62a90, 0xa7a72d41, 0x7a097802, 0x326f3386, 0xe55c89e1, 0x4e07b948, 0x87f72e27,
    0xff80a07f, 0x52143f6c, 0xb1e910e5, 0x8fbf2171, 0x8b08852c, 0xe7f02db3, 0xbcbf2f72, 0x73aeb0f4, 0xb04860b7, 0x021d420f, 0xe511e6b2, 0xa18d3bfa, 0xcd810125, 0x6c0f6995, 0x04b5c883, 0x855d3727,
    0x54bda785, 0x012dbc9f, 0xda1df9d0, 0x1b0049e5, 0xd03d4545, 0x25739796, 0xd731f50f, 0x0a15e6a8, 0xe008d6a1, 0xc0b61d07, 0x0c6c6af2, 0xb394cdcb, 0x42e79aeb, 0x624f87b9, 0x4de0618c, 0xb8904ca5,
    0x48a009d1, 0x61dfd44d, 0x8003f29d, 0xf26b6648, 0x807f23c6, 0x8dc91131, 0x2924511c, 0xb5f19592, 0x0d72ffc4, 0x5319b168, 0xf71a17c4, 0x630e76de, 0xd8002c8b, 0x3fe9bb02, 0x81c33d2e, 0xee736a17,
    0xf9a76f9c, 0x886a0b44, 0xe2e98780, 0x8c924545, 0x25572247, 0xfeec84fa, 0x6224c17f, 0x7e96853d, 0x150757ae, 0x6106673f, 0x78a036dd, 0x873c2f16, 0xd9970225, 0xfc91c075, 0xb8894bea, 0xe7ea9e15,
    0x7f49a6ca, 0x29b0fa49, 0x87546c3b, 0x9da84372, 0x094c6f40, 0x535d30a8, 0x920880ef, 0x231287d0, 0x5b880350, 0x06d24773, 0x25345ef9, 0x22e53315, 0x3f84d3cc, 0x052f476f, 0x167e5b4e, 0x97883121,
    0xab103770, 0xf696c99f, 0xfc5aac08, 0xaeeac278, 0xdecf0ffd, 0x2ca3b8c5, 0xe3994027, 0xfc232aea, 0x318838db, 0x52d4b7cc, 0x489b8b88, 0x19b1369d, 0x1c264d6c, 0xce8b628a, 0x57a0429c, 0x9f82412d,
    0x1779ba86, 0x74bbe34e, 0x1fc4800c, 0x5368e375, 0x2ff13d98, 0x350a1c16, 0xe120334b, 0x0d344123, 0x9295800b, 0xa5006ccd, 0x4f0c1ea5, 0x10d77ede, 0x8ba7796a, 0xafe8d49b, 0x4b71ead3, 0x2cdc9b17,
    0xdca000f0, 0xdca2bc16, 0x070cd051, 0xfd4fba20, 0x2aef7ad3, 0xfffde2ff, 0xec989e91, 0xb35470ab, 0xb651b969, 0xb93fd51d, 0x86e20762, 0xf68b0974, 0x5701bb07, 0xd07b5046, 0x0f180f4d, 0xa8a3ad4c,
    0xab8ae4d2, 0x8d5f4700, 0x5c4144d7, 0x1c527db3, 0xd341179a, 0xe91abb7a, 0xd6f4d2c3, 0xba4c1340, 0xe00f7f3d, 0xa1ff5869, 0x2867a8a3, 0x6221331a, 0x1784019c, 0x8356105e, 0xca94aabd, 0xbb71b386,
    0x7018b286, 0x62c5d6c6, 0x4a7b9b17, 0x601aabe5, 0x7be6ecf7, 0x7774ab39, 0x6ffda7c8, 0x2564f24c, 0x2cbd14a6, 0xd98f6fa6, 0x00a7849d, 0x642da29c, 0xba08c868, 0xb2988d2b, 0x3fa97a62, 0x1fc12fbf,
    0x25e81815, 0xff6c5f08, 0xeb804598, 0xc887e90f, 0xcdba5e4d, 0xe68566b1, 0x0a8d450b, 0xab8ff540, 0x2829590b, 0xcce5e827, 0xefc7b330, 0x3be45ae3, 0x18137e22, 0xa2c727ca, 0xa48efbe2, 0x45cd0525,
    0x2d9ad9f0, 0xa54a0025, 0x9260aa4d, 0x2e1d4c69, 0xe1a0221c, 0x2db68fce, 0xd0f6ded7, 0xe1ff3407, 0xddf4bc5b, 0x11a3dcd3, 0xa0f82535, 0x667a5577, 0x54cd288f, 0xa4e97c8d, 0xce0507b9, 0xe2dac75c,
    0x8f53616a, 0xc1553c2c, 0xc9b9c019, 0xac34c5f6, 0x4e49df8c, 0x27a21e4a, 0xcaa98e67, 0x80dc8bbe, 0x38246cd0, 0x5afde629, 0xd36a8675, 0x59f50d70, 0x748ffc9b, 0xda6e468c, 0x687f543e, 0xdf01b11e,
    0x3c713477, 0xc27e3d38, 0xf82eec5b, 0x9243af0b, 0xe04a04e2, 0x888b19b3, 0x67b86725, 0x73443f22, 0xe6e4aa09, 0xd3559c8b, 0xd8615f92, 0xbf0a7a26, 0x1a1e4410, 0x448e7306, 0x0f06d723, 0x1387661c,
    0xf073b98b, 0x6fe4191a, 0xa75cdc77, 0x7fe6461d, 0x20d2249c, 0x7e27ea00, 0x175a4e49, 0x0746bf0e, 0x64a69788, 0x22a7f258, 0x3a93846f, 0xf80abdc9, 0x2dc08384, 0x4b6eb7c7, 0x7ae7e134, 0x014c5da2,
    0xcce6c1bd, 0x32520561, 0xd602155a, 0x2bdcf94f, 0x0382e265, 0x9d94b4c5, 0x6ee9e955, 0xd9182e7c, 0x5b557732, 0xda41ac67, 0xd63034ce, 0xdd2a005c, 0xe6284ed5, 0x83a621bb, 0xd0c29af8, 0x6b1ea68c,
    0xb561e9b4, 0x96b9a3c0, 0xdba9ebf1, 0x1dce9d6c, 0x8c511116, 0x730b54a6, 0x0a8f59bd, 0x3114fa49, 0x45482e5d, 0xa40b19c0, 0x5209afad, 0x8349d76c, 0x3df1d603, 0x99c53cb3, 0x144f9635, 0x1a66d7b0,
    0x1c1a0e3d, 0xb9f46ec0, 0xf155e852, 0x73a6b8c3, 0xffec50a9, 0xd48afdbc, 0xe483127c, 0x226f896d, 0xd3a38478, 0x7e27b7d2, 0xf2ea1deb, 0xe69b22fe, 0xfdd0d942, 0x63d9c236, 0x4dc04423, 0xc45bb578,
    0x3401a1f9, 0xcccce0e8, 0xe5c23254, 0x17aa93cb, 0xde3e9f84, 0xa43b45c9, 0x04384662, 0x478ba253, 0x66d49daf, 0xbaacd610, 0x24e1903a, 0x89586569, 0xa8bd73e1, 0x029aeaf0, 0x1179a496, 0xe7c03dc1,
    0x6205c5c6, 0x8f6ed938, 0x65ad6993, 0xcb8786ab, 0x1d5c79c9, 0x1cb20f58, 0x1730290a, 0x05334734, 0x84bd903c, 0x8314915e, 0xeefc3dbc, 0x64cfe9fb, 0x68e13574, 0xb592e94a, 0x082b7525, 0x7623349a,
    0xcfc2f626, 0xb8b48034, 0x83f9620e, 0x14a40ece, 0x09648e06, 0xf5a71313, 0x54c1c640, 0xa8fc21fa, 0x9debe041, 0x7bc6e326, 0x5b9817e6, 0x3c800fdf, 0xf843c277, 0x6b4c9514, 0x5dbf2d84, 0x221bf0da,
    0x3eca2aa5, 0xa4a7f070, 0xa92f2c6e, 0xdf88d03d, 0xad839668, 0xa42ed0dd, 0xf42c696c, 0x0ec73f99, 0x44877ce0, 0x5bcc687a, 0x84252dcb, 0xaa88c1a9, 0x6e4375f3, 0xd0f91c55, 0x86aa78a9, 0x80c48d82,
    0xc84435c3, 0x1878228a, 0x06efb6d2, 0x5238736d, 0x731df51b, 0x33209524, 0x02a2e9cb, 0x4c6663a7, 0xa8dd1b4f, 0xe9ca993f, 0x36ad681b, 0xd3189cb2, 0x68c63b8f, 0x5a5e9168, 0x10ae0f56, 0x8c3ac244,
    0x608469a2, 0xd22fa8e7, 0x1ef02c02, 0xf347854f, 0x3522315e, 0x85063417, 0xfd93dcaf, 0xac9a2757, 0x2d1b3ee0, 0x10dc33c8, 0xe4617ae5, 0xa6c99f56, 0x52a4a5e6, 0x65964daa, 0x751cbd82, 0x7db7c547,
    0x3e7ebaaf, 0x95a96777, 0x36ca2723, 0x8dd04810, 0xd24dbf25, 0x61cd08e5, 0xecade1f0, 0xd8f54089, 0xde5e2124, 0x90f5d4de, 0x6fccc25b, 0xd7c97d21, 0x4c235434, 0xa21951c8, 0xd84f9771, 0xc22d5a41,
    0x499ed7e7, 0x40903413, 0xb292962d, 0x369784d5, 0x88537a95, 0x32aba59f, 0xecc71a4c, 0x58a1125a, 0x4c3e4add, 0x2e39ae6d, 0x5c9f8e93, 0xaf9cf27a, 0xb4a105f2, 0xd0b2e49d, 0xce3350d9, 0xe9441e8f,
    0x9ef88bbd, 0xaedf5299, 0x686b3335, 0xc15377a4, 0x274a69ac, 0x8546f1e9, 0x17f86ce1, 0x8275f8d8, 0xaf77f9b8, 0x749c52f1, 0x846c68b4, 0x65c2ba4b, 0x14023fe8, 0xceba198d, 0x8db60f7d, 0x01142e15,
    0xae2c9364, 0xc3ae8953, 0x59d71456, 0xdea7288e, 0xd9e5ca52, 0x1a794538, 0x55b3f739, 0x4581bb0f, 0x02d06bb7, 0x44a608ef, 0xc98dac77, 0xf1b58a23, 0xe0027ce3, 0xb5f8e635, 0xda88ff88, 0x92bca470,
    0x27d00b04, 0xabf45b43, 0xfb518718, 0xe43103b0, 0x512dab31, 0x533f6a9f, 0x5c84cfd0, 0x0a186149, 0x0fa31628, 0xc0df407f, 0xc40bfe94, 0x008c54ea, 0xe6248135, 0xccba28c0, 0x2915a13b, 0x35bb6b36,
    0x4d1108bf, 0x0f244cfa, 0x7700e95a, 0x3c2ab7b8, 0x580da514, 0x191339b2, 0x0d3a848f, 0x1e58f372, 0x73da6e2d, 0x69bd1967, 0xded8b9ae, 0x109dd58b, 0x92e00705, 0xe1b4e5b1, 0xd69ff7f3, 0xc6a88a23,
    0xbf75aeae, 0x1f6bcbbc, 0xb8d6479e, 0xea966204, 0x1ed5f1c1, 0x9cd206d3, 0x1fc904b4, 0xf80e7189, 0x9606db15, 0x9aecda13, 0x9d598ab2, 0xa42b045b, 0x85d30aab, 0x7ba9e76b, 0xd5be1562, 0xc033b0fb,
    0xb950f16f, 0x2f2fa1d9, 0x9e30a653, 0x1bf62397, 0x478f6fd7, 0xeed50428, 0x2a8211a2, 0x06bd9e62, 0xba786255, 0xe318779d, 0x6fea7602, 0x176879f4, 0x6cc89246, 0x0b1b7155, 0x94c3ba59, 0xdd26ba1d};

static int c[N * N];

int do_matmul()
{
    matmul(a, b, c);
    return c[c[0] & (N * N - 1)];
}

#ifdef WITH_MAIN
#include <stdio.h>
int main()
{
    printf("code = %d\n", do_matmul() & 0x7fffffff);
}
#endif
