export const defaultTask = {
	id: "",
	phase: "capture",
	title: "",
	parentId: "",
	ft: "",
	description: "",
	context: "",
	time: "",
	enegery: "",
	completed: "",
	isCalendar: false,
	order: 1,
	calendar: {
		startTime: "date",
		endTime: "date",
		repeated: {
			enable: true,
			frequency: "1",
			day: "",
			month: "",
			year: "",
		},
		calendarRef: [{}],
	},
};
