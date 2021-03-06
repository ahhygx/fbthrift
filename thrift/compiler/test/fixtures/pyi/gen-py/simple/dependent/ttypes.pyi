#
# Autogenerated by Thrift
#
# DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
#  @generated
#
import typing as t

from thrift import Thrift
from thrift.protocol.TProtocol import TProtocolBase

__property__ = property  # sometimes `property` is used as a field name


UTF8STRINGS: bool


class ItemEnum(int):
    OPTION_ONE: t.ClassVar[ItemEnum]
    OPTION_TWO: t.ClassVar[ItemEnum]

    _VALUES_TO_NAMES: t.ClassVar[t.Dict[ItemEnum, str]]
    _NAMES_TO_VALUES: t.ClassVar[t.Dict[str, ItemEnum]]


class Item:
    thrift_spec: t.Tuple[t.Optional[t.Tuple[int, int, str, t.Any, t.Optional[int], int]]]
    thrift_field_annotations: t.Dict[int, t.Dict[str, str]]
    thrift_struct_annotations: t.Dict[str, str]

    def __init__(
        self,
        key: t.Optional[str] = ...,
        value: t.Optional[bytes] = ...,
        enum_value: t.Optional[ItemEnum] = ...
    ) -> None:
        ...

    @__property__
    def key(self) -> str: ...
    @key.setter
    def key(self, value: t.Optional[str]) -> None: ...
    @__property__
    def value(self) -> t.Optional[bytes]: ...
    @value.setter
    def value(self, value: t.Optional[bytes]) -> None: ...
    @__property__
    def enum_value(self) -> ItemEnum: ...
    @enum_value.setter
    def enum_value(self, value: t.Optional[ItemEnum]) -> None: ...


    def isUnion(self) -> bool: ...
    def checkRequired(self) -> None: ...
    def read(self, iprot: TProtocolBase) -> None: ...
    def write(self, oprot: TProtocolBase) -> None: ...
    def __eq__(self, other: t.Any) -> bool: ...
    def __ne__(self, other: t.Any) -> bool: ...
