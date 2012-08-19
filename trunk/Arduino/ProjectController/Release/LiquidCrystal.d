008" {
			OVERRIDE_VALUE 49 
		}
		MACRO "ReferencePoint" {
			AFTER_MOTION Yes 
		}
	}
	WORD_VALUE "G" "40" {
		VARIABLE "4007"
		MACRO "CutterCompOff"
		MACRO "Cancel3dToolOffset"
	}
	WORD_VALUE "G" "41" {
		VARIABLE "4007"
		MACRO "CutterCompLeft"
	}
	WORD_VALUE "G" "42" {
		VARIABLE "4007"
		MACRO "CutterCompRight"
	}
	WORD_VALUE "G" "43" {
		VARIABLE "4008"
		MACRO "ToolLengthCompPos"
	}
	WORD_VALUE "G" "44" {
		VARIABLE "4008"
		MACRO "ToolLengthCompNeg"
	}
	WORD_VALUE "G" "49" {
		VARIABLE "4008"
		MACRO "ToolLengthCompOff"
		MACRO "RtcpOff"
	}
	WORD_VALUE "G" "52" {
		MACRO "AbsoluteShiftNum" {
			OVERRIDE_VALUE 1 
		}
	}
	WORD_VALUE "G" "53" {
		MACRO "NullMacro"
	}
	WORD_VALUE "G" "54-59" {
		VARIABLE "4014"
		MACRO "WorkCoord"
	}
	WORD_VALUE "G" "60" {
		MACRO "IgnoreMacro"
	}
	WORD