import os
import typing as t
import tempfile

import cg_at_utils.utils as utils
import typer

def install() -> t.NoReturn:
    """Install dependencies"""

    # Install packages with `apt`. This will quit the wrapper with an error code
    # if an error occurred.
    utils.pkg.apt('default-jdk', 'default-jre')

    utils.run_cmds(
        check=True,
        exit_after=False,
    )

    # Install packages with `pip`. This will quit the wrapper with an error code
    # if an error occurred.
    utils.pkg.pip('junitparser==2.0.0')

def parse_junit_xml(tree):
    """Read the xml file, parse it, and remove tags
    are not yet supported by CodeGrade.
    """
    for _, el in tree:
        _, _, el.tag = el.tag.rpartition('}')

    root = tree.root
    if root.tag == 'testsuite':
        print("failures " + str(root.get('failures')))
        if int(root.get('failures')) != 0:
            root.set('failures', '1')
        root.set('tests', '1')

    for child in list(root):
        if child.tag == 'testcase':
            child.set('classname', 'This style category')
            child.set('time', '1')
        if child.tag != 'testcase':
            root.remove(child)
    return root


def run(
    runner_args: t.List[str] = typer.Argument(
        ...,
        help=(
            'Arguments to pass to the JUnit ConsoleLauncher'
            ' https://junit.org/junit5/docs/current/user-guide/#running-tests-console-launcher'
        ),
        metavar='JUNIT_ARGS',
    ),
) -> t.NoReturn:
    """Run the unit tests"""

    # We cannot import `junitparser` at the top of this file, because it is
    # not yet installed (this happens in the `install` stage).
    import junitparser.junitparser as jparser

    # classpath = set_classpath()
    junit_xml = utils.junit_xml.get_location(delete=True)

    with tempfile.TemporaryDirectory() as xml_dir:
        utils.run_cmds(
            [
                'python3',
                'cpplint.py',
                *runner_args,
                # '2> cpplint_output.xml',
                
            ],
            exit_after=False,
        )

        merged_report = jparser.JUnitXml()

        for report_file in [
            'cpplint_output.xml',
        ]:
            report = parse_junit_xml(
                jparser.etree.iterparse(report_file),
            )
            merged_report.append(jparser.JUnitXml.fromelem(report))

        merged_report.write(junit_xml)

        utils.exit(0)


app = utils.cli.make_wrapper(
    # The name of the script and a helpful message that appear in the `--help`
    # output.
    name='cg-cpplint',  
    help='A wrapper script for running cpplint tests',
    install=install,
    run=run,           # The function for the `run` stage.
)

if __name__ == '__main__':
    app()
