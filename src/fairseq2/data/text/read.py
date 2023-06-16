# Copyright (c) Meta Platforms, Inc. and affiliates.
# All rights reserved.
#
# This source code is licensed under the BSD-style license found in the
# LICENSE file in the root directory of this source tree.

from enum import Enum
from typing import TYPE_CHECKING, List, Optional

from fairseq2 import DOC_MODE
from fairseq2.data.data_pipeline import DataPipelineBuilder
from fairseq2.data.string import StringLike
from fairseq2.data.typing import PathLike

if TYPE_CHECKING or DOC_MODE:

    class LineEnding(Enum):
        INFER = 0
        LF = 1
        CRLF = 2

    def read_text(
        pathname: PathLike,
        encoding: Optional[StringLike] = None,
        line_ending: LineEnding = LineEnding.INFER,
        ltrim: bool = False,
        rtrim: bool = False,
        skip_empty: bool = False,
        skip_header: int = 0,
        memory_map: bool = False,
        block_size: Optional[int] = None,
    ) -> DataPipelineBuilder:
        ...

    class TextSplitter:
        def __init__(self, sep: str = "\t") -> None:
            ...

        def __call__(self, s: StringLike) -> List[StringLike]:
            ...

else:
    from fairseq2.C.data.text import LineEnding as LineEnding
    from fairseq2.C.data.text import TextSplitter as TextSplitter
    from fairseq2.C.data.text import read_text as read_text

    def _set_module_name() -> None:
        for t in [LineEnding, TextSplitter, read_text]:
            t.__module__ = __name__

    _set_module_name()
