copy ..\\Objects\app.hex .\\nRF52_DFU.hex
nrfutil dfu genpkg DFU_HB044_V114_0621_1154.zip --application nRF52_DFU.hex --application-version 0xFFFFFFFF --dev-revision 0xFFFF --dev-type 0xFFFF --sd-req 0xFFFE
del .\\nRF52_DFU.hex
pause